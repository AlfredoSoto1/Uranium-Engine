#include <utility>

module uranium.services;

namespace uranium::services {
    
    Logger::Logger() noexcept {
    
    }

    Logger::~Logger() noexcept {

    }

    std::string Logger::toString(LogLevel level) noexcept {
        switch (level) {
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::WARN:
            return "WARN";
        case LogLevel::TRACE:
            return "TRACE";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
        }
    }

    std::pair<Logger::ConsoleTextColor, Logger::ConsoleTextColor> Logger::toColor(LogLevel level) noexcept {
        switch (level) {
        case LogLevel::INFO:
            return { ConsoleTextColor::YELLOW, ConsoleTextColor::WHITE };
        case LogLevel::DEBUG:
            return { ConsoleTextColor::BLUE,   ConsoleTextColor::WHITE };
        case LogLevel::WARN:
            return { ConsoleTextColor::YELLOW, ConsoleTextColor::YELLOW };
        case LogLevel::TRACE:
            return { ConsoleTextColor::GREEN,  ConsoleTextColor::WHITE };
        case LogLevel::ERROR:
            return { ConsoleTextColor::RED,    ConsoleTextColor::WHITE };
        case LogLevel::FATAL:
            return { ConsoleTextColor::RED,    ConsoleTextColor::RED };
        default:
            return { ConsoleTextColor::WHITE,  ConsoleTextColor::WHITE };
        }
    }
}
