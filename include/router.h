#pragma once

#include <unordered_map>
#include <functional>
#include <string>

class Router
{
public:
    using Handler = std::function<std::string()>;

    void addRoute(const std::string& path, Handler handler);

    bool hasRoute(const std::string& path) const;

    std::string handle(const std::string& path);

private:
    std::unordered_map<std::string, Handler> routes_;
};