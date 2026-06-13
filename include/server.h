#pragma once

#include <winsock2.h>

#include "router.h"

class Server
{
public:
    explicit Server(int port);

    void start();

private:
    void handleClient(SOCKET clientSocket, int clientId);

private:
    int port_;
    Router router_;
};