#include "router.h"

void Router::addRoute(const std::string& path, Handler handler)
{
    routes_[path] = std::move(handler);
}

bool Router::hasRoute(
    const std::string& path) const
{
    return routes_.find(path) != routes_.end();
}

std::string Router::handle(
    const std::string& path)
{
    auto it = routes_.find(path);

    if (it == routes_.end())
        return "";

    return it->second();
}