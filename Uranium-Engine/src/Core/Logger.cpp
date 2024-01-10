#include "Logger.h"

#include <iostream>
#include <cstdarg>

namespace Uranium::Core {
    
    Logger* Logger::logger = nullptr;

    void Logger::init() noexcept {
        Logger::logger = new Logger();
    }
    
    void Logger::shutdown() noexcept {
        delete Logger::logger;
    }
    
    Logger::Logger() noexcept {

    }

    Logger::~Logger() {

    }

    Logger& Logger::instance() noexcept {
        return *Logger::logger;
    }

    void Logger::consolePrint(LogLevel level, const char* type, const char* format, ...) noexcept {

        char buffer[512]; // 512B
        va_list args;
        va_start(args, format);
        std::vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);

        const char* endOfMessageColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::WHITE)];
        
        switch (level) {
        case LogLevel::INFO:
            {
                const char* headerColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::YELLOW)];
                std::cout << headerColor << "[Uranium: INFO] " << type << " " << endOfMessageColor << buffer << std::endl;
                break;
            }
        case LogLevel::DEBUG:
            {
                const char* headerColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::BLUE)];
                std::cout << headerColor << "[Uranium: DEBUG] " << type << " " << endOfMessageColor << buffer << std::endl;
                break;
            }
        case LogLevel::WARN:
            {
                const char* headerColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::GREEN)];
                const char* messageColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::YELLOW)];
                std::cout << headerColor << "[Uranium: WARN] " << type << " " << messageColor << buffer << endOfMessageColor << std::endl;
                break;
            }
        case LogLevel::TRACE:
            {
                const char* headerColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::GREEN)];
                std::cout << headerColor << "[Uranium: TRACE] " << type << " " << endOfMessageColor << buffer << std::endl;
                break;
            }
        case LogLevel::ERROR:
            {
                const char* headerColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::RED)];
                std::cout << headerColor << "[Uranium: ERROR] " << type << " " << endOfMessageColor << buffer << std::endl;
                break;
            }
        case LogLevel::FATAL:
            {
                const char* headerColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::RED)];
                std::cout << headerColor << "[Uranium: FATAL] " << type << " " << buffer << endOfMessageColor << std::endl;
                break;
            }
        }
    }

    void Logger::filePrint(/*Select file output here*/LogLevel level, const char* type, const char* format, ...) noexcept {

    }
}