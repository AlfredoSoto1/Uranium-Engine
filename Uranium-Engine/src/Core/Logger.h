#include <string>
#include <iostream>

#include "CoreMacros.h"

namespace Uranium::Core {

    /*
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

    /*
    * Console Text Color enum definitions
    * These define the console text color,
    * these are orderer in a way that match
    * the color codes for the next statement.
    */
    URANIUM_API enum class ConsoleTextColor {
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
    * Color codes literal definitions
    * These define the color code to be
    * inserted in the console to print.
    */
    URANIUM_API constexpr const char* s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::COUNT)] = {
        "\033[0;30m",  // BLACK
        "\033[0;31m",  // RED
        "\033[0;32m",  // GREEN
        "\033[0;33m",  // YELLOW
        "\033[0;34m",  // BLUE
        "\033[0;35m",  // MAGENTA
        "\033[0;36m",  // CYAN
        "\033[0;37m"   // WHITE
    };

    class URANIUM_API Logger final {
    public:
        /*
        * Initiates the Logger singleton
        */
        static void init() noexcept;

        /*
        * Shuts down the logger singleton.
        * This frees all memory allocated by the single instance
        */
        static void shutdown() noexcept;

        /*
        * Returns the unique reference to the logger
        */
        static Logger& instance() noexcept;

    public:
        /*
        */
        void consolePrint(LogLevel level, const std::string& message) noexcept;

        /*
        */
        void filePrint(/*Select file output here*/LogLevel level, const std::string& message) noexcept;

    private:
        explicit Logger() noexcept;

        ~Logger();

    private:
        static Logger* logger;
    };

    /*
    */
#define UR_ERROR(message) Logger::instance().consolePrint(LogLevel::WARN,  message)

    /*
    */
#if defined(UR_DEBUG)
#define UR_INFO(message)  Logger::instance().consolePrint(LogLevel::INFO,  message)
#define UR_TRACE(message) Logger::instance().consolePrint(LogLevel::TRACE, message)
#define UR_WARN(message)  Logger::instance().consolePrint(LogLevel::WARN,  message)

#define UR_ASSERT(condition, message)


#elif defined(UR_RELEASE)
#define UR_INFO(message) 
#define UR_TRACE(message)
#define UR_WARN(message) 

#endif




    static void print(ConsoleTextColor headerColor, ConsoleTextColor messageColor, const std::string& header, const std::string& message) {
            
        const char* headerColorCode = s_ColorCodes[static_cast<uint32_t>(headerColor)];
        const char* messageColorCode = s_ColorCodes[static_cast<uint32_t>(messageColor)];

        std::cout                                             << 
        headerColorCode << "[" << header << "] "              << // print header with default color
        s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::WHITE)] << // set the color back to white
        messageColorCode << message                           << // print the message and with the selected color
        s_ColorCodes[static_cast<uint32_t>(ConsoleTextColor::WHITE)] << // set the color back to white
        std::endl;
    }

#ifdef UR_DEBUG
#define UR_TRACE(message) print(ConsoleTextColor::GREEN,  ConsoleTextColor::WHITE, "[Uranium TRACE]: ", message);
#define UR_WARN(message)  print(ConsoleTextColor::YELLOW, ConsoleTextColor::WHITE, "[Uranium TRACE]: ", message);
#define UR_ERROR(message) print(ConsoleTextColor::RED,    ConsoleTextColor::WHITE, "[Uranium TRACE]: ", message);
#endif // UR_DEBUG
}
