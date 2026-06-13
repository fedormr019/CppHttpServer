cmake_minimum_required(VERSION 3.15)

project(Logger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Logger
    src/main.cpp
    src/logger.cpp
    src/http.cpp
    src/router.cpp
    src/server.cpp
)

target_link_libraries(Logger ws2_32)