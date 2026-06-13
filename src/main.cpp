#include "server.h"
#include "logger.h"

int main()
{
    Logger::get().setLogFile("server.log");

    LOG_INFO("Application started");

    Server server(8080);

    server.start();

    return 0;
}