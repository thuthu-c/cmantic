#pragma once

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

enum LogLevel
{
    TRACE = 0,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger
{
  public:
    Logger(LogLevel minLevel, const std::string &filename = "") : logLevel(minLevel)
    {
        if (!filename.empty())
        {
            logFile.open(filename, std::ios::app);
            if (!logFile.is_open())
            {
                std::cerr << "Failed to open log file, using stdout only." << std::endl;
            }
        }
    }

    ~Logger()
    {
        if (logFile.is_open())
            logFile.close();
    }

    void logTrace(const std::string &message)
    {
        log(TRACE, "TRACE", message);
    }

    void logDebug(const std::string &message)
    {
        log(DEBUG, "DEBUG", message);
    }

    void logInfo(const std::string &message)
    {
        log(INFO, "INFO", message);
    }

    void logWarning(const std::string &message)
    {
        log(WARNING, "WARNING", message);
    }

    void logError(const std::string &message, bool exitOnError = true)
    {
        log(ERROR, "ERROR", message);
        if (exitOnError)
        {
            std::exit(1);
        }
    }

    void logCritical(const std::string &message, bool exitOnError = true)
    {
        log(CRITICAL, "CRITICAL", message);
        if (exitOnError)
        {
            std::exit(1);
        }
    }

  private:
    LogLevel logLevel;
    std::ofstream logFile;

    void log(LogLevel level, const std::string &levelStr, const std::string &message)
    {
        if (level < logLevel)
            return;

        // Timestamp
        std::time_t now = std::time(nullptr);
        std::tm *timeinfo = std::localtime(&now);
        char timestamp[20];
        std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

        std::ostringstream logEntry;
        logEntry << "[" << timestamp << "] " << levelStr << ": " << message << "\n";

        // Console
        std::cout << logEntry.str();

        // File
        if (logFile.is_open())
        {
            logFile << logEntry.str();
            logFile.flush();
        }
    }
};

extern Logger logger;