#pragma once

namespace uranium::core {
    /*
    * @brief
    * Forward declaration of Application class to access the
    * application log singleton instance service.
    */
    class Application;
}

namespace uranium::services {
/*
* Evaluate these macros in debug configuration ONLY
*/
#if defined(UR_DEBUG)
    /*
    * An error occurred. The program may need to handle this.
    *
    * @param format
    */
    #define UR_ERROR(header, format, ...) Application::instance().log().consolePrint(LogLevel::ERROR, header, format, __VA_ARGS__)

    /*
    * Application cannot continue, must close program entirely
    *
    * @param header
    * @param format
    */
    #define UR_FATAL(header, format, ...) Application::instance().log().consolePrint(LogLevel::FATAL, header, format __VA_OPT__(,) __VA_ARGS__)

    /*
    * Provides information to the client through the console
    * 
    * @param header
    * @param format
    */
    #define UR_INFO(header, format, ...)  Application::instance().log().consolePrint(LogLevel::INFO, header, format __VA_OPT__(,) __VA_ARGS__)

    /*
    * Provides detailed trace information
    *
    * @param header
    * @param format
    */
    #define UR_TRACE(header, format, ...) Application::instance().log().consolePrint(LogLevel::TRACE, header, format __VA_OPT__(,) __VA_ARGS__)

    /*
    * A warning occurred, but the program can continue
    *
    * @param header
    * @param format
    */
    #define UR_WARN(header, message, ...) Application::instance().log().consolePrint(LogLevel::WARN, header, format __VA_OPT__(,) __VA_ARGS__)
    
    /*
    * This is evaluated at run-time
    * 
    * @param condition - establishes if it should do an assert
    * @param message   - displays the message of the assertion
    */
    #define UR_ASSERT(condition, header, message) \
    {                                             \
        if (condition) {                          \
            services::UR_ERROR(header, message);  \
            UR_DEBUG_BREAK();                     \
        }                                         \
    }                                             \

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
    * 
    * @param header
    * @param format
    */
    #define UR_ERROR(header, format, ...) Application::instance().log().filePrint(LogLevel::ERROR, header, format __VA_OPT__(,) __VA_ARGS__)

    /*
    * Application cannot continue, must close program entirely
    * Writes to a log file the fatal error.
    *
    * @param header
    * @param format
    */
    #define UR_FATAL(header, format, ...) Application::instance().log().filePrint(LogLevel::FATAL, header, format __VA_OPT__(,) __VA_ARGS__)

    #define UR_INFO(header,  format, ...) Application::instance().log().filePrint(LogLevel::INFO,  header, format __VA_OPT__(,) __VA_ARGS__)
    #define UR_TRACE(header, format, ...) /*Nothing*/
    #define UR_WARN(header,  format, ...) /*Nothing*/

    #define UR_ASSERT(condition, header, format)
    #define UR_STATIC_ASSERT(condition, message)

#elif defined(UR_DISTRIBUTION)
    /*
    * An error occurred. The program may need to handle this.
    * Writes to a log file the error.
    * 
    * @param header
    * @param format
    */
    #define UR_ERROR(header, format, ...) Application::instance().log().filePrint(LogLevel::ERROR, header, format __VA_OPT__(,) __VA_ARGS__)

    /*
    * Application cannot continue, must close program entirely
    * Writes to a log file the fatal error.
    *
    * @param type
    * @param message
    */
    #define UR_FATAL(header, format, ...) Application::instance().log().filePrint(Core::LogLevel::FATAL, header, format __VA_OPT__(,) __VA_ARGS__)

    #define UR_INFO(header,  format, ...) /*Nothing*/
    #define UR_TRACE(header, format, ...) /*Nothing*/
    #define UR_WARN(header,  format, ...) /*Nothing*/

    #define UR_ASSERT(condition, header, format) /*Nothing*/
    #define UR_STATIC_ASSERT(condition, message) /*Nothing*/

#else
    #error No build configuration defined. Must be Debug, Release, Distribution.
#endif
}