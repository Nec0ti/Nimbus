#pragma once

#include <string>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace Nimbus {

    /**
     * @brief Log levels for the engine
     */
    enum class LogLevel {
        Trace = SPDLOG_LEVEL_TRACE,
        Debug = SPDLOG_LEVEL_DEBUG,
        Info = SPDLOG_LEVEL_INFO,
        Warning = SPDLOG_LEVEL_WARN,
        Error = SPDLOG_LEVEL_ERROR,
        Critical = SPDLOG_LEVEL_CRITICAL
    };

    /**
     * @brief Logging system for the Nimbus Engine
     * 
     * The Log class provides a centralized logging system using spdlog.
     * It supports multiple log levels, console and file output, and
     * formatted logging with various sinks.
     */
    class Log {
    public:
        /**
         * @brief Initialize the logging system
         * @param logPath Path to store log files
         * @param maxFileSize Maximum size of log files in bytes
         * @param maxFiles Maximum number of log files to keep
         */
        static void Initialize(const std::string& logPath = "logs/", 
                              size_t maxFileSize = 1024 * 1024 * 5, // 5MB
                              size_t maxFiles = 3);

        /**
         * @brief Shutdown the logging system
         */
        static void Shutdown();

        /**
         * @brief Set the log level
         * @param level Log level to set
         */
        static void SetLevel(LogLevel level);

        /**
         * @brief Get the current log level
         * @return Current log level
         */
        static LogLevel GetLevel();

        /**
         * @brief Log a message
         * @param level Log level
         * @param message Message to log
         */
        static void Log(LogLevel level, const std::string& message);

        /**
         * @brief Log a trace message
         * @param message Message to log
         */
        template<typename... Args>
        static void Trace(const std::string& message, Args&&... args) {
            if (s_logger) {
                s_logger->trace(message, std::forward<Args>(args)...);
            }
        }

        /**
         * @brief Log a debug message
         * @param message Message to log
         */
        template<typename... Args>
        static void Debug(const std::string& message, Args&&... args) {
            if (s_logger) {
                s_logger->debug(message, std::forward<Args>(args)...);
            }
        }

        /**
         * @brief Log an info message
         * @param message Message to log
         */
        template<typename... Args>
        static void Info(const std::string& message, Args&&... args) {
            if (s_logger) {
                s_logger->info(message, std::forward<Args>(args)...);
            }
        }

        /**
         * @brief Log a warning message
         * @param message Message to log
         */
        template<typename... Args>
        static void Warning(const std::string& message, Args&&... args) {
            if (s_logger) {
                s_logger->warn(message, std::forward<Args>(args)...);
            }
        }

        /**
         * @brief Log an error message
         * @param message Message to log
         */
        template<typename... Args>
        static void Error(const std::string& message, Args&&... args) {
            if (s_logger) {
                s_logger->error(message, std::forward<Args>(args)...);
            }
        }

        /**
         * @brief Log a critical message
         * @param message Message to log
         */
        template<typename... Args>
        static void Critical(const std::string& message, Args&&... args) {
            if (s_logger) {
                s_logger->critical(message, std::forward<Args>(args)...);
            }
        }

        /**
         * @brief Flush all pending log messages
         */
        static void Flush();

        /**
         * @brief Get the underlying spdlog logger
         * @return Pointer to the spdlog logger
         */
        static std::shared_ptr<spdlog::logger> GetLogger() { return s_logger; }

    private:
        static std::shared_ptr<spdlog::logger> s_logger;
        static bool s_initialized;
    };

} // namespace Nimbus