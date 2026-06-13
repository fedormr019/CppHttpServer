#include "logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

Logger& Logger::get()
{
    static Logger instance;
    return instance;
}

Logger::Logger()
    : currentLevel_(LogLevel::Debug)
{
}

void Logger::setLevel(LogLevel level)
{
    currentLevel_ = level;
}

bool Logger::setLogFile(const std::string& filename)
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (logfile_.is_open())
    {
        logfile_.close();
    }

    logfile_.open(filename, std::ios::app);

    return logfile_.is_open();
}

std::string Logger::levelToString(LogLevel level) const
{
    switch (level)
    {
    case LogLevel::Debug:
        return "DEBUG";

    case LogLevel::Info:
        return "INFO";

    case LogLevel::Warn:
        return "WARN";

    case LogLevel::Error:
        return "ERROR";
    }

    return "UNKNOWN";
}

void Logger::log(LogLevel level,
    const std::string& message,
    const char* file,
    int line)
{
    if (static_cast<int>(level) < static_cast<int>(currentLevel_))
    {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::tm tm{};

    localtime_s(&tm, &time);

    std::ostringstream stream;

    stream << "["
        << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
        << "] "
        << "["
        << levelToString(level)
        << "] "
        << "["
        << file
        << ":"
        << line
        << "] "
        << message;

    const std::string output = stream.str();

    std::cout << output << '\n';

    if (logfile_.is_open())
    {
        logfile_ << output << '\n';
        logfile_.flush();
    }
}