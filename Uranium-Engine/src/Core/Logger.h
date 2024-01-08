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
        void consolePrint(LogLevel level, const char* message) noexcept;

        /*
        */
        void filePrint(/*Select file output here*/LogLevel level, const char* message) noexcept;

    private:
        /*
        */
        explicit Logger() noexcept;

        ~Logger();

    private:
        static Logger* logger;

        /*
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


/*
* Evaluate these macros in debug configuration ONLY
*/
#if defined(UR_DEBUG)

/*
* An error occurred. The program may need to handle this.
*
* @param message
*/
#define UR_ERROR(message) Logger::instance().consolePrint(LogLevel::ERROR,  message)

/*
* Application cannot continue, must close program entirely
*
* @param message
*/
#define UR_FATAL(message) Logger::instance().consolePrint(LogLevel::FATAL,  message)

/*
* Provides information to the client through the console
* 
* @param message
*/
#define UR_INFO(message)  Logger::instance().consolePrint(LogLevel::INFO,  message)

/*
* Provides detailed trace information
*
* @param message
*/
#define UR_TRACE(message) Logger::instance().consolePrint(LogLevel::TRACE, message)

/*
* A warning occurred, but the program can continue
*
* @param message
*/
#define UR_WARN(message)  Logger::instance().consolePrint(LogLevel::WARN,  message)
    
/*
* This is evaluated at run-time
* 
* @param condition - establishes if it should do an assert
* @param message   - displays the message of the assertion
*/
#define UR_ASSERT(condition, message) \
{                                     \
    if (condition) {                  \
        UR_ERROR(message);            \
        UR_DEBUG_BREAK();             \
    }                                 \
}                                     \

/*
* This is evaluated at compile-time
* 
* @param condition - establishes if it should do an assert
* @param message   - displays the message of the assertion
*/
#define UR_STATIC_ASSERT(condition, message) \
{                                            \
    static_assert(condition, message);       \
}                                            \

#elif defined(UR_RELEASE)

/*
* An error occurred. The program may need to handle this.
* Writes to a log file the error.
* @param message
*/
#define UR_ERROR(message) Logger::instance().filePrint(LogLevel::ERROR,  message)

/*
* Application cannot continue, must close program entirely
* Writes to a log file the fatal error.
*
* @param message
*/
#define UR_FATAL(message) Logger::instance().filePrint(LogLevel::FATAL,  message)

#define UR_INFO(message)  Logger::instance().filePrint(LogLevel::INFO,  message)
#define UR_TRACE(message) /*Nothing*/
#define UR_WARN(message)  /*Nothing*/

#define UR_ASSERT(condition, message)
#define UR_STATIC_ASSERT(condition, message)

#elif defined(UR_DISTRIBUTION)

/*
* An error occurred. The program may need to handle this.
* Writes to a log file the error.
* @param message
*/
#define UR_ERROR(message) Logger::instance().filePrint(LogLevel::ERROR,  message)

/*
* Application cannot continue, must close program entirely
* Writes to a log file the fatal error.
*
* @param message
*/
#define UR_FATAL(message) Logger::instance().filePrint(LogLevel::FATAL,  message)

#define UR_INFO(message)  /*Nothing*/
#define UR_TRACE(message) /*Nothing*/
#define UR_WARN(message)  /*Nothing*/

#define UR_ASSERT(condition, message)        /*Nothing*/
#define UR_STATIC_ASSERT(condition, message) /*Nothing*/

#endif
}
