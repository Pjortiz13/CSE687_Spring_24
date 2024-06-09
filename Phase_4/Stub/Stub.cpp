#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <thread>
#include <vector>
#include <chrono>
#include <fstream>
#include <mutex>
#include <map>

#pragma comment(lib, "Ws2_32.lib")

typedef void(*MapFunction)(const std::string&, std::map<std::string, int>&);
typedef void(*ReduceFunction)(const std::map<std::string, int>&, std::map<std::string, int>&);

std::mutex logMutex;

void logMessage(const std::string& message) {
    std::lock_guard<std::mutex> guard(logMutex);
    std::ofstream logFile("log.txt", std::ios::app);
    logFile << message << std::endl;
    logFile.close();
}

void sendHeartbeat(SOCKET controllerSocket, const std::string& processType) {
    while (true) {
        std::string heartbeatMessage = processType + " heartbeat";
        send(controllerSocket, heartbeatMessage.c_str(), static_cast<int>(heartbeatMessage.size()), 0);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void handleClient(SOCKET clientSocket, const std::string& mapperDLL, const std::string& reducerDLL) {
    char recvbuf[512];
    int recvbuflen = 512;
    int iResult;

    // Receive data from client
    iResult = recv(clientSocket, recvbuf, recvbuflen, 0);
    if (iResult > 0) {
        std::string message(recvbuf, static_cast<size_t>(iResult));
        logMessage("Received message: " + message);

        if (message == "map") {
            HINSTANCE mapLib = LoadLibraryA(mapperDLL.c_str());
            if (!mapLib) {
                logMessage("Failed to load mapper DLL: " + std::to_string(GetLastError()));
                return;
            }
            MapFunction mapper = (MapFunction)GetProcAddress(mapLib, "map");
            if (!mapper) {
                logMessage("Failed to load map function: " + std::to_string(GetLastError()));
                FreeLibrary(mapLib);
                return;
            }

            // Perform map operation
            std::map<std::string, int> mapOutput;
            mapper("example input data for map function", mapOutput);

            FreeLibrary(mapLib);
            logMessage("Map process completed");
        }
        else if (message == "reduce") {
            HINSTANCE reduceLib = LoadLibraryA(reducerDLL.c_str());
            if (!reduceLib) {
                logMessage("Failed to load reducer DLL: " + std::to_string(GetLastError()));
                return;
            }
            ReduceFunction reducer = (ReduceFunction)GetProcAddress(reduceLib, "reduce");
            if (!reducer) {
                logMessage("Failed to load reduce function: " + std::to_string(GetLastError()));
                FreeLibrary(reduceLib);
                return;
            }

            // Perform reduce operation
            std::map<std::string, int> mapOutput; // Should be filled with map results
            std::map<std::string, int> reduceOutput;
            reducer(mapOutput, reduceOutput);

            FreeLibrary(reduceLib);
            logMessage("Reduce process completed");
        }
    }

    // Close the socket
    closesocket(clientSocket);
}

int main() {
    WSADATA wsaData;
    int iResult;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        logMessage("WSAStartup failed with error: " + std::to_string(iResult));
        return 1;
    }

    struct addrinfo* result = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, "12345", &hints, &result);
    if (iResult != 0) {
        logMessage("getaddrinfo failed with error: " + std::to_string(iResult));
        WSACleanup();
        return 1;
    }

    SOCKET listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        logMessage("socket failed with error: " + std::to_string(WSAGetLastError()));
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    iResult = bind(listenSocket, result->ai_addr, static_cast<int>(result->ai_addrlen));
    if (iResult == SOCKET_ERROR) {
        logMessage("bind failed with error: " + std::to_string(WSAGetLastError()));
        freeaddrinfo(result);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        logMessage("listen failed with error: " + std::to_string(WSAGetLastError()));
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    logMessage("Server is listening on port 12345");

    std::vector<std::thread> clientThreads;

    while (true) {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            logMessage("accept failed with error: " + std::to_string(WSAGetLastError()));
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        clientThreads.emplace_back(handleClient, clientSocket, "libMap.dll", "libReduce.dll");

        // Start heartbeat thread for each process type
        std::thread(&sendHeartbeat, clientSocket, "Map").detach();
        std::thread(&sendHeartbeat, clientSocket, "Reduce").detach();
    }

    for (auto& thread : clientThreads) {
        thread.join();
    }

    closesocket(listenSocket);
    WSACleanup();

    return 0;
}
