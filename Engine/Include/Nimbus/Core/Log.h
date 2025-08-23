#pragma once

#include "Nimbus/Core/Base.h"
#include <string>
#include <memory>

namespace Nimbus {

    enum class LogLevel
    {
        Trace = 0,
        Debug = 1,
        Info = 2,
        Warn = 3,
        Error = 4,
        Fatal = 5
    };

    class NIMBUS_API Logger
    {
    public:
        Logger(const std::string& name);
        ~Logger() = default;

        template<typename... Args>
        void Log(LogLevel level, const std::string& format, Args&&... args);

        template<typename... Args>
        void Trace(const std::string& format, Args&&... args) { Log(LogLevel::Trace, format, std::forward<Args>(args)...); }

        template<typename... Args>
        void Debug(const std::string& format, Args&&... args) { Log(LogLevel::Debug, format, std::forward<Args>(args)...); }

        template<typename... Args>
        void Info(const std::string& format, Args&&... args) { Log(LogLevel::Info, format, std::forward<Args>(args)...); }

        template<typename... Args>
        void Warn(const std::string& format, Args&&... args) { Log(LogLevel::Warn, format, std::forward<Args>(args)...); }

        template<typename... Args>
        void Error(const std::string& format, Args&&... args) { Log(LogLevel::Error, format, std::forward<Args>(args)...); }

        template<typename... Args>
        void Fatal(const std::string& format, Args&&... args) { Log(LogLevel::Fatal, format, std::forward<Args>(args)...); }

        void SetLevel(LogLevel level) { m_Level = level; }
        LogLevel GetLevel() const { return m_Level; }

    private:
        std::string m_Name;
        LogLevel m_Level = LogLevel::Trace;

        void LogImpl(LogLevel level, const std::string& message);
        std::string FormatMessage(LogLevel level, const std::string& message);
        std::string LevelToString(LogLevel level);
        std::string GetTimestamp();
    };

    class NIMBUS_API Log
    {
    public:
        static void Init();
        static void Shutdown();

        static Ref<Logger>& GetCoreLogger() { return s_CoreLogger; }
        static Ref<Logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static Ref<Logger> s_CoreLogger;
        static Ref<Logger> s_ClientLogger;
    };

    // Template implementations
    template<typename... Args>
    void Logger::Log(LogLevel level, const std::string& format, Args&&... args)
    {
        if (level < m_Level)
            return;

        std::string message;
        if constexpr (sizeof...(args) > 0)
        {
            message = FormatString(format, std::forward<Args>(args)...);
        }
        else
        {
            message = format;
        }

        LogImpl(level, message);
    }

    // String formatting helper
    template<typename... Args>
    std::string FormatString(const std::string& format, Args&&... args)
    {
        // Simple implementation - in a real engine you'd use fmt or similar
        std::ostringstream oss;
        FormatImpl(oss, format, std::forward<Args>(args)...);
        return oss.str();
    }

    template<typename T>
    void FormatImpl(std::ostringstream& oss, const std::string& format, T&& value)
    {
        size_t pos = format.find("{0}");
        if (pos != std::string::npos)
        {
            oss << format.substr(0, pos) << value << format.substr(pos + 3);
        }
        else
        {
            oss << format;
        }
    }

    template<typename T, typename... Args>
    void FormatImpl(std::ostringstream& oss, const std::string& format, T&& value, Args&&... args)
    {
        size_t pos = format.find("{0}");
        if (pos != std::string::npos)
        {
            std::string newFormat = format.substr(0, pos) + std::to_string(value) + format.substr(pos + 3);
            // Replace subsequent placeholders
            for (size_t i = 1; i <= sizeof...(args); ++i)
            {
                std::string placeholder = "{" + std::to_string(i) + "}";
                std::string newPlaceholder = "{" + std::to_string(i - 1) + "}";
                size_t replacePos = 0;
                while ((replacePos = newFormat.find(placeholder, replacePos)) != std::string::npos)
                {
                    newFormat.replace(replacePos, placeholder.length(), newPlaceholder);
                    replacePos += newPlaceholder.length();
                }
            }
            FormatImpl(oss, newFormat, std::forward<Args>(args)...);
        }
        else
        {
            oss << format;
        }
    }
}

// Core log macros
#define NIMBUS_CORE_TRACE(...) ::Nimbus::Log::GetCoreLogger()->Trace(__VA_ARGS__)
#define NIMBUS_CORE_DEBUG(...) ::Nimbus::Log::GetCoreLogger()->Debug(__VA_ARGS__)
#define NIMBUS_CORE_INFO(...)  ::Nimbus::Log::GetCoreLogger()->Info(__VA_ARGS__)
#define NIMBUS_CORE_WARN(...)  ::Nimbus::Log::GetCoreLogger()->Warn(__VA_ARGS__)
#define NIMBUS_CORE_ERROR(...) ::Nimbus::Log::GetCoreLogger()->Error(__VA_ARGS__)
#define NIMBUS_CORE_FATAL(...) ::Nimbus::Log::GetCoreLogger()->Fatal(__VA_ARGS__)

// Client log macros
#define NIMBUS_TRACE(...) ::Nimbus::Log::GetClientLogger()->Trace(__VA_ARGS__)
#define NIMBUS_DEBUG(...) ::Nimbus::Log::GetClientLogger()->Debug(__VA_ARGS__)
#define NIMBUS_INFO(...)  ::Nimbus::Log::GetClientLogger()->Info(__VA_ARGS__)
#define NIMBUS_WARN(...)  ::Nimbus::Log::GetClientLogger()->Warn(__VA_ARGS__)
#define NIMBUS_ERROR(...) ::Nimbus::Log::GetClientLogger()->Error(__VA_ARGS__)
#define NIMBUS_FATAL(...) ::Nimbus::Log::GetClientLogger()->Fatal(__VA_ARGS__)