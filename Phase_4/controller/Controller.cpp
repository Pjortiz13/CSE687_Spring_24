#include <iostream>
#include <string>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <chrono>
#include <fstream>

#pragma comment(lib, "Ws2_32.lib")

void logMessage(const std::string& message) {
    std::ofstream logFile("controller_log.txt", std::ios::app);
    logFile << message << std::endl;
    logFile.close();
}

void sendCommand(const std::string& address, const std::string& port, const std::string& command) {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
        logMessage("WSAStartup failed with error: " + std::to_string(iResult));
        return;
    }

    struct addrinfo* result = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(address.c_str(), port.c_str(), &hints, &result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed with error: " << iResult << std::endl;
        logMessage("getaddrinfo failed with error: " + std::to_string(iResult));
        WSACleanup();
        return;
    }

    SOCKET connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (connectSocket == INVALID_SOCKET) {
        std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
        logMessage("socket failed with error: " + std::to_string(WSAGetLastError()));
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    iResult = connect(connectSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "connect failed with error: " << WSAGetLastError() << std::endl;
        logMessage("connect failed with error: " + std::to_string(WSAGetLastError()));
        closesocket(connectSocket);
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    iResult = send(connectSocket, command.c_str(), (int)command.size(), 0);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
        logMessage("send failed with error: " + std::to_string(WSAGetLastError()));
    }
    else {
        logMessage("Sent command: " + command + " to " + address + ":" + port);
    }

    closesocket(connectSocket);
    freeaddrinfo(result);
    WSACleanup();
}

int main() {
    std::vector<std::pair<std::string, std::string>> stubs = {
        {"127.0.0.1", "12345"}
        // Add more stub addresses and ports as needed
    };

    for (const auto& stub : stubs) {
        sendCommand(stub.first, stub.second, "map");
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate delay
        sendCommand(stub.first, stub.second, "reduce");
    }

    return 0;
}
