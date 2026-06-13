#include "server.h"
#include "http.h"
#include "logger.h"

#include <thread>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

Server::Server(int port) : port_(port)
{
    router_.addRoute("/", []()
        {
            return "Home page";
        });

    router_.addRoute("/ping", []()
        {
            return "pong";
        });

    router_.addRoute("/about", []()
        {
            return "My first C++ backend";
        });
}

void Server::handleClient(SOCKET clientSocket, int clientId)
{
    char buffer[4096];

    int bytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytes <= 0)
    {
        closesocket(clientSocket);
        return;
    }

    buffer[bytes] = '\0';

    std::string rawRequest(buffer);

    HttpRequest request = parseRequest(rawRequest);

    LOG_INFO(request.method + " " + request.path);

    std::string response;

    if (router_.hasRoute(request.path))
    {
        response = buildResponse(router_.handle(request.path));
    }

    else
    {
        LOG_WARN("404 " + request.path);

        response = buildResponse("404 Not Found", 404, "Not Found");
    }

    send(clientSocket, response.c_str(), static_cast<int>(response.size()), 0);

    closesocket(clientSocket);
}

void Server::start()
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        LOG_ERROR("WSAStartup failed");
        return;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port_);

    if (bind(serverSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        LOG_ERROR("Bind failed");
        return;
    }

    listen(serverSocket, SOMAXCONN);

    LOG_INFO("Server started on port " + std::to_string(port_));

    int clientId = 0;

    while (true)
    {
        sockaddr_in clientAddr{};
        int len = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &len);

        if (clientSocket == INVALID_SOCKET)
        {
            continue;
        }

        LOG_INFO("Client connected");

        std::thread(&Server::handleClient, this, clientSocket, clientId++).detach();
    }
}