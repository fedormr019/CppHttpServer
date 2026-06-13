#pragma once

#include <string>

struct HttpRequest
{
    std::string method;
    std::string path;
};

HttpRequest parseRequest(const std::string& request);

std::string buildResponse(const std::string& body, int statusCode = 200, const std::string& statusText = "OK");