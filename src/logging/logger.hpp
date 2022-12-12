#pragma once

#ifndef PBR_PIPELINE_LOGGER_HPP
#define PBR_PIPELINE_LOGGER_HPP

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/fmt.h>
#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <regex>
#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <iostream>
#include <sstream>

namespace PBRPipeline::Logger {
    const std::string reset = "\033[m";
    const std::string bold = "\033[1m";
    const std::string blue = "\033[34m";
    const std::string magenta = "\033[35m";
    const std::string cyan = "\033[36m";

    static constexpr const char* const DATETIME_LITERAL_FORMAT = "%Y-%m-%d_%H-%M-%S";
    static constexpr const char* const LOG_FORMAT = "[{}{}%Y-%m-%d %H:%M:%S{}] [Thread: {}%t{}] [{}%n{}] [{}%^%-5l%${}] :: %v";

    std::string formatTime(const char *formatString);

    static inline std::string encodeAnsiColours() {
        return fmt::format(
            LOG_FORMAT,
            magenta,
            bold,
            reset,
            blue,
            reset,
            cyan,
            reset,
            bold,
            reset
        );
    }

    static std::string getLogFileName() {
        return "../logs/gl_colour_grading_" + formatTime(DATETIME_LITERAL_FORMAT) + ".log";
    }

    static void generalErrorHandler(const std::string& msg) {
        spdlog::error("[EXCEPTION] :: {0}", msg);
    }

    static void init(spdlog::level::level_enum consoleLevel,
                     spdlog::level::level_enum fileLevel) {
        try {
            std::vector<spdlog::sink_ptr> sinks;

            auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            stdoutSink->set_level(consoleLevel);
            stdoutSink->set_pattern(encodeAnsiColours());
            sinks.push_back(stdoutSink);

            std::shared_ptr<spdlog::sinks::basic_file_sink<std::mutex>> basicFileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(getLogFileName());
            basicFileSink->set_level(fileLevel);
            basicFileSink->set_pattern(std::regex_replace(LOG_FORMAT, std::regex("\\{\\}"), ""));
            sinks.push_back(basicFileSink);

            std::shared_ptr<spdlog::logger> combinedLogger = std::make_shared<spdlog::logger>("GLCG", begin(sinks), end(sinks));
            spdlog::set_default_logger(combinedLogger);
            combinedLogger->set_level(spdlog::level::trace);

            spdlog::set_error_handler(PBRPipeline::Logger::generalErrorHandler);
        } catch (const spdlog::spdlog_ex& ex) {
            spdlog::set_pattern(encodeAnsiColours());
            spdlog::error("Custom logger init failed: {}", ex.what());
            exit(1);
        }
    }

    static void init() {
        init(spdlog::level::trace, spdlog::level::trace);
    }

    static void errorCallbackGLFW(int code, const char* message) {
        spdlog::error("GLFW Error ({0}): {1}", code, message);
    }
}

#endif // PBR_PIPELINE_LOGGER_HPP