#include "Logger.h"

#if defined(UR_PLATFORM_WINDOWS)
#include <cstdarg>
#include <iostream>
#endif

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

#if defined(UR_PLATFORM_WINDOWS)

    void Logger::consolePrint(LogLevel level, const char* message) noexcept {

        const char* endOfMessageColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::WHITE)];
        
        switch (level) {
        case LogLevel::INFO:
            {
                const char* headerColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::YELLOW)];
                std::cout << headerColor << "[Uranium: INFO] " << endOfMessageColor << message << std::endl;
                break;
            }
        case LogLevel::DEBUG:
            {
                const char* headerColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::BLUE)];
                std::cout << headerColor << "[Uranium: DEBUG] " << endOfMessageColor << message << std::endl;
                break;
            }
        case LogLevel::WARN:
            {
                const char* headerColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::GREEN)];
                const char* messageColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::YELLOW)];
                std::cout << headerColor << "[Uranium: WARN] " << messageColor << message << endOfMessageColor << std::endl;
                break;
            }
        case LogLevel::TRACE:
            {
                const char* headerColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::GREEN)];
                std::cout << headerColor << "[Uranium: TRACE] " << endOfMessageColor << message << std::endl;
                break;
            }
        case LogLevel::ERROR:
            {
                const char* headerColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::RED)];
                std::cout << headerColor << "[Uranium: ERROR] " << endOfMessageColor << message << std::endl;
                break;
            }
        case LogLevel::FATAL:
            {
                const char* headerColor = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::RED)];
                std::cout << headerColor << "[Uranium: FATAL] " << message << endOfMessageColor << std::endl;
                break;
            }
        }
    }

    void Logger::filePrint(/*Select file output here*/LogLevel level, const char* message) noexcept {

    }

#else
    void Logger::consolePrint(LogLevel level, const char* message) noexcept {

    }

    void Logger::filePrint(/*Select file output here*/LogLevel level, const char* message) noexcept {

    }

#endif
}


//static void print(ConsoleTextColor headerColor, ConsoleTextColor messageColor, const std::string& header, const std::string& message) {
//        
//    const char* headerColorCode = s_ColorCodes[static_cast<uint32_t>(headerColor)];
//    const char* messageColorCode = s_ColorCodes[static_cast<uint32_t>(messageColor)];

//    std::cout                                             << 
//    headerColorCode << "[" << header << "] "              << // print header with default color
//    s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::WHITE)] << // set the color back to white
//    messageColorCode << message                           << // print the message and with the selected color
//    s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::WHITE)] << // set the color back to white
//    std::endl;
//}