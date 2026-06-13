#include "http.h"

HttpRequest parseRequest(const std::string& request)
{
    HttpRequest result;

    size_t firstSpace = request.find(' ');

    if (firstSpace == std::string::npos)
        return result;

    size_t secondSpace = request.find(' ', firstSpace + 1);

    if (secondSpace == std::string::npos)
        return result;

    result.method = request.substr(0, firstSpace);

    result.path = request.substr(
        firstSpace + 1,
        secondSpace - firstSpace - 1);

    return result;
}

std::string buildResponse(const std::string& body, int statusCode, const std::string& statusText)
{
    return
        "HTTP/1.1 " +
        std::to_string(statusCode) +
        " " +
        statusText +
        "\r\n"
        "Content-Type: text/plain; charset=utf-8\r\n"
        "Content-Length: " +
        std::to_string(body.size()) +
        "\r\n"
        "Connection: close\r\n"
        "\r\n" +
        body;
}