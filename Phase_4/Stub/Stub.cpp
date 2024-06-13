// stub.cpp
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
#include <filesystem>

#pragma comment(lib, "Ws2_32.lib")

typedef void(__cdecl* MapFunction)(const char*, const char*, const char*, int);
typedef void(__cdecl* ReduceFunction)(const char*, const char*);

std::mutex logMutex;

void logMessage(const std::string& message) {
    std::lock_guard<std::mutex> guard(logMutex);
    std::ofstream logFile("stub_log.txt", std::ios::app);
    logFile << message << std::endl;
    logFile.close();
    std::cout << message << std::endl; // Ensure logging is also output to the console for debugging
}

void sendHeartbeat(SOCKET controllerSocket, const std::string& processType) {
    while (true) {
        if (controllerSocket == INVALID_SOCKET) {
            logMessage("Invalid socket, stopping heartbeat.");
            break;
        }
        std::string heartbeatMessage = processType + " heartbeat";
        if (send(controllerSocket, heartbeatMessage.c_str(), static_cast<int>(heartbeatMessage.size()), 0) == SOCKET_ERROR) {
            logMessage("Heartbeat send failed: " + std::to_string(WSAGetLastError()));
            break; // Exit loop if sending fails
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void handleClient(SOCKET clientSocket, const std::string& mapperDLL, const std::string& reducerDLL) {
    char recvbuf[512] = { 0 };
    int iResult = recv(clientSocket, recvbuf, sizeof(recvbuf), 0);
    if (iResult <= 0) {
        logMessage("recv failed: " + std::to_string(WSAGetLastError()));
        closesocket(clientSocket);
        return;
    }

    std::string message(recvbuf, iResult);
    logMessage("Received message: " + message);

    if (message == "map_func") {
        HINSTANCE mapLib = LoadLibraryA(mapperDLL.c_str());
        if (!mapLib) {
            logMessage("Failed to load mapper DLL: " + std::to_string(GetLastError()));
            return;
        }
        MapFunction mapper = (MapFunction)GetProcAddress(mapLib, "map_func");
        if (!mapper) {
            logMessage("Failed to load map function: " + std::to_string(GetLastError()));
            FreeLibrary(mapLib);
            return;
        }

        const char* inputData = "sample data for map function";
        mapper("example.txt", inputData, "C:/temp", 4);
        FreeLibrary(mapLib);
        logMessage("Map process completed.");
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

        std::string mapOutputPath = "C:/temp/mapper_output_0.txt";
        std::string reduceOutputPath = "C:/temp/reduce_output.txt";
        if (!std::filesystem::exists(mapOutputPath)) {
            logMessage("File does not exist: " + mapOutputPath);
            return;
        }

        reducer(mapOutputPath.c_str(), reduceOutputPath.c_str());
        FreeLibrary(reduceLib);
        logMessage("Reduce process completed.");
    }

    // Send acknowledgment back to the controller
    std::string ackMessage = message + " completed";
    if (send(clientSocket, ackMessage.c_str(), static_cast<int>(ackMessage.size()), 0) == SOCKET_ERROR) {
        logMessage("Failed to send acknowledgment: " + std::to_string(WSAGetLastError()));
    }

    closesocket(clientSocket);
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        logMessage("WSAStartup failed: " + std::to_string(WSAGetLastError()));
        return 1;
    }

    struct addrinfo* result = nullptr, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(nullptr, "12345", &hints, &result) != 0) {
        logMessage("getaddrinfo failed: " + std::to_string(WSAGetLastError()));
        WSACleanup();
        return 1;
    }

    SOCKET listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        logMessage("socket failed: " + std::to_string(WSAGetLastError()));
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    if (bind(listenSocket, result->ai_addr, static_cast<int>(result->ai_addrlen)) == SOCKET_ERROR) {
        logMessage("bind failed: " + std::to_string(WSAGetLastError()));
        freeaddrinfo(result);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        logMessage("listen failed: " + std::to_string(WSAGetLastError()));
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    logMessage("Server is listening on port 12345");

    std::vector<std::thread> clientThreads;
    while (true) {
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            logMessage("accept failed: " + std::to_string(WSAGetLastError()));
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        clientThreads.emplace_back(handleClient, clientSocket, "libMap.dll", "libReduce.dll");

        // Start heartbeat thread
        std::thread(&sendHeartbeat, clientSocket, "stub").detach();
    }

    for (auto& thread : clientThreads) {
        thread.join();
    }

    closesocket(listenSocket);
    WSACleanup();

    return 0;
}
