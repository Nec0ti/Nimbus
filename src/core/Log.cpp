#include "core/Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <filesystem>

namespace Nimbus {

    std::shared_ptr<spdlog::logger> Log::s_logger = nullptr;
    bool Log::s_initialized = false;

    void Log::Initialize(const std::string& logPath, size_t maxFileSize, size_t maxFiles) {
        if (s_initialized) {
            return;
        }

        try {
            // Create log directory if it doesn't exist
            std::filesystem::create_directories(logPath);

            // Create console sink
            auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            consoleSink->set_pattern("[%H:%M:%S.%e] [%^%l%$] [%s:%#] %v");

            // Create file sink
            auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                logPath + "/nimbus_engine.log", maxFileSize, maxFiles);
            fileSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%s:%#] %v");

            // Create logger with both sinks
            s_logger = std::make_shared<spdlog::logger>("NimbusEngine", 
                spdlog::sinks_init_list{consoleSink, fileSink});

            // Set as default logger
            spdlog::set_default_logger(s_logger);

            // Set default log level
            s_logger->set_level(spdlog::level::info);

            s_initialized = true;
            s_logger->info("Logging system initialized");

        } catch (const std::exception& e) {
            // Fallback to console-only logging
            s_logger = spdlog::stdout_color_mt("NimbusEngine");
            s_logger->error("Failed to initialize file logging: {}", e.what());
            s_initialized = true;
        }
    }

    void Log::Shutdown() {
        if (s_logger) {
            s_logger->info("Logging system shutting down");
            spdlog::shutdown();
            s_logger = nullptr;
        }
        s_initialized = false;
    }

    void Log::SetLevel(LogLevel level) {
        if (s_logger) {
            s_logger->set_level(static_cast<spdlog::level::level_enum>(level));
        }
    }

    LogLevel Log::GetLevel() {
        if (s_logger) {
            return static_cast<LogLevel>(s_logger->level());
        }
        return LogLevel::Info;
    }

    void Log::Log(LogLevel level, const std::string& message) {
        if (s_logger) {
            s_logger->log(static_cast<spdlog::level::level_enum>(level), message);
        }
    }

    void Log::Flush() {
        if (s_logger) {
            s_logger->flush();
        }
    }

} // namespace Nimbus