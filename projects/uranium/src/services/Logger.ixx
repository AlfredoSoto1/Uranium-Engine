module;
#include "core/URAPI.h"
#include <format>

export module uranium.services;

import <iostream>;
export import <string>;

export namespace uranium::services {
    /*
    * @brief
    * Log Level enum definitions
    * These define the level of logging
    */
    URANIUM_API enum class LogLevel {
        INFO = 0,
        DEBUG,
        WARN,
        TRACE,
        ERROR,
        FATAL,
        COUNT
    };

    URANIUM_API class Logger final {
    public:
        explicit Logger() noexcept;
        ~Logger() noexcept;

    public:
        /*
        * @brief
        * Prints to the console information with a log level
        * 
        * @param level
        * @param format
        * @param args
        */
        void consolePrint(LogLevel level, const std::string& header, const std::string& format, auto ...args) noexcept {
            // Convert to a console text color enum the given log level
            auto [open, close] = toColor(level);

            // Obtain the actual ascii code that changes the text color on console
            const char* openColor = s_ColorCodes[static_cast<uint32_t>(open)];
            const char* closeColor = s_ColorCodes[static_cast<uint32_t>(close)];
            const char* closePrinting = s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::WHITE)];
            
            constexpr int tagWidth = 5;

            // Obtain the buffer string that joins the formatted
            // message with the arguments provided
            std::string message = std::vformat(format, std::make_format_args(args...));
            std::string headerBuffer = std::format("{}[{:<{}}] {}{} {}{}", openColor, toString(level), tagWidth, header, closeColor, message, closePrinting);

            // Print the actual message
            std::cout << headerBuffer << std::endl;
        }

        /*
        * @brief
        * Prints to a log file information
        * 
        * @param format
        * @param ... message
        */
        void filePrint(LogLevel level, const std::string& header, const std::string& format, auto ...args) noexcept {
            // File print logic here
        }

        /*
        * @brief
        * Dumps data into the given file path
        * 
        * @param format
        * @param ... message
        */
        void dump(LogLevel level, const std::string& header, const std::string& format, auto ...args) noexcept {
            // Dump logic here
        }

        /*
        * @brief
        * Converts to string the log level enum value
        * 
        * @returns log level string
        */
        std::string toString(LogLevel level) noexcept;

    private:
        /*
        * @brief
        * Console Text Color enum definitions
        * These define the console text color,
        * these are orderer in a way that match
        * the color codes for the next statement.
        */
        enum class ConsoleTextColor {
            BLACK = 0,
            RED,
            GREEN,
            YELLOW,
            BLUE,
            MAGENTA,
            CYAN,
            WHITE,
            COUNT
        };
        
        /*
        * @brief
        * Converts the log level to color enum
        * for later mapping to color code
        * 
        * @returns pair of opening and closing console color
        */
        std::pair<ConsoleTextColor, ConsoleTextColor> toColor(LogLevel level) noexcept;

        /*
        * @brief
        * Color codes literal definitions
        * These define the color code to be
        * inserted in the console to print.
        */
        const char* s_ColorCodes[static_cast<unsigned int>(ConsoleTextColor::COUNT)] = {
            "\033[0;30m",  // BLACK
            "\033[0;31m",  // RED
            "\033[0;32m",  // GREEN
            "\033[0;33m",  // YELLOW
            "\033[0;34m",  // BLUE
            "\033[0;35m",  // MAGENTA
            "\033[0;36m",  // CYAN
            "\033[0;37m"   // WHITE
        };
    };
}
