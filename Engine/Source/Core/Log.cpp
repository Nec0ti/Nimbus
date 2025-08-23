#include "NimbusPCH.h"
#include "Nimbus/Core/Log.h"

#include <iostream>
#include <iomanip>
#include <ctime>

namespace Nimbus {

    Ref<Logger> Log::s_CoreLogger;
    Ref<Logger> Log::s_ClientLogger;

    void Log::Init()
    {
        s_CoreLogger = CreateRef<Logger>("NIMBUS");
        s_ClientLogger = CreateRef<Logger>("APP");

        NIMBUS_CORE_INFO("Nimbus Engine Logging System Initialized");
    }

    void Log::Shutdown()
    {
        NIMBUS_CORE_INFO("Nimbus Engine Logging System Shutdown");
        s_CoreLogger.reset();
        s_ClientLogger.reset();
    }

    Logger::Logger(const std::string& name)
        : m_Name(name)
    {
    }

    void Logger::LogImpl(LogLevel level, const std::string& message)
    {
        std::string formattedMessage = FormatMessage(level, message);
        
        // Output to console with color coding
        switch (level)
        {
            case LogLevel::Trace:
                std::cout << "\033[37m" << formattedMessage << "\033[0m" << std::endl;
                break;
            case LogLevel::Debug:
                std::cout << "\033[36m" << formattedMessage << "\033[0m" << std::endl;
                break;
            case LogLevel::Info:
                std::cout << "\033[32m" << formattedMessage << "\033[0m" << std::endl;
                break;
            case LogLevel::Warn:
                std::cout << "\033[33m" << formattedMessage << "\033[0m" << std::endl;
                break;
            case LogLevel::Error:
                std::cerr << "\033[31m" << formattedMessage << "\033[0m" << std::endl;
                break;
            case LogLevel::Fatal:
                std::cerr << "\033[41m\033[37m" << formattedMessage << "\033[0m" << std::endl;
                break;
        }
    }

    std::string Logger::FormatMessage(LogLevel level, const std::string& message)
    {
        std::ostringstream oss;
        oss << "[" << GetTimestamp() << "] [" << m_Name << "] [" << LevelToString(level) << "] " << message;
        return oss.str();
    }

    std::string Logger::LevelToString(LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Trace: return "TRACE";
            case LogLevel::Debug: return "DEBUG";
            case LogLevel::Info:  return "INFO";
            case LogLevel::Warn:  return "WARN";
            case LogLevel::Error: return "ERROR";
            case LogLevel::Fatal: return "FATAL";
        }
        return "UNKNOWN";
    }

    std::string Logger::GetTimestamp()
    {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time_t), "%H:%M:%S");
        oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
        return oss.str();
    }

}