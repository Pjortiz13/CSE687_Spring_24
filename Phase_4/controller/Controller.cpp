// controller.cpp
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
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        logMessage("WSAStartup failed.");
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }

    struct addrinfo* result = nullptr, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(address.c_str(), port.c_str(), &hints, &result) != 0) {
        logMessage("getaddrinfo failed.");
        std::cerr << "getaddrinfo failed." << std::endl;
        WSACleanup();
        return;
    }

    SOCKET connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (connectSocket == INVALID_SOCKET) {
        logMessage("socket failed.");
        std::cerr << "socket failed." << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    if (connect(connectSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        logMessage("connect failed.");
        std::cerr << "connect failed." << std::endl;
        closesocket(connectSocket);
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    if (send(connectSocket, command.c_str(), (int)command.size(), 0) == SOCKET_ERROR) {
        logMessage("send failed.");
        std::cerr << "send failed." << std::endl;
    }
    else {
        logMessage("Sent command: " + command + " to " + address + ":" + port);
        std::cout << "Sent command: " + command + " to " + address + ":" + port << std::endl;
    }

    // Receiving response
    char recvbuf[512] = { 0 };
    int recvResult = recv(connectSocket, recvbuf, 512, 0);
    if (recvResult > 0) {
        std::string response(recvbuf, static_cast<size_t>(recvResult));
        logMessage("Received response: " + response);
        std::cout << "Received response: " + response << std::endl;
    }
    else {
        logMessage("No response or error: " + std::to_string(WSAGetLastError()));
        std::cerr << "No response or error: " + std::to_string(WSAGetLastError()) << std::endl;
    }

    closesocket(connectSocket);
    freeaddrinfo(result);
    WSACleanup();
}

int main() {
    std::vector<std::pair<std::string, std::string>> stubs = {
        {"127.0.0.1", "12345"}
    };

    for (const auto& stub : stubs) {
        sendCommand(stub.first, stub.second, "map_func");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        sendCommand(stub.first, stub.second, "reduce");
    }

    return 0;
}
