#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <mutex>
#include <string>

enum class LogLevel
{
    Debug,
    Info,
    Warn,
    Error
};

class Logger
{
public:
    static Logger& get();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void setLevel(LogLevel level);

    bool setLogFile(const std::string& filename);

    void log(LogLevel level,const std::string& message, const char* file, int line);

private:
    Logger();

    std::string levelToString(LogLevel level) const;

private:
    LogLevel currentLevel_;
    std::mutex mutex_;
    std::ofstream logfile_;
};

#define LOG_DEBUG(msg) \
    Logger::get().log(LogLevel::Debug, msg, __FILE__, __LINE__)

#define LOG_INFO(msg) \
    Logger::get().log(LogLevel::Info, msg, __FILE__, __LINE__)

#define LOG_WARN(msg) \
    Logger::get().log(LogLevel::Warn, msg, __FILE__, __LINE__)

#define LOG_ERROR(msg) \
    Logger::get().log(LogLevel::Error, msg, __FILE__, __LINE__)

#endif