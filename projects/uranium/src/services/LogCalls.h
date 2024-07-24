//#pragma once
//
//#include "Logger.h"
//
//namespace uranium::core {
///*
//* Evaluate these macros in debug configuration ONLY
//*/
//#if defined(UR_DEBUG)
//    /*
//    * An error occurred. The program may need to handle this.
//    *
//    * @param message
//    */
//    #define UR_ERROR(type, message, ...) Logger::instance().consolePrint(Core::LogLevel::ERROR, type, message, __VA_ARGS__)
//
//    /*
//    * Application cannot continue, must close program entirely
//    *
//    * @param type
//    * @param message
//    */
//    #define UR_FATAL(type, message, ...) Logger::instance().consolePrint(Core::LogLevel::FATAL, type, message, __VA_ARGS__)
//
//    /*
//    * Provides information to the client through the console
//    * 
//    * @param type
//    * @param message
//    */
//    #define UR_INFO(type, message, ...)  Logger::instance().consolePrint(Core::LogLevel::INFO, type, message, __VA_ARGS__)
//
//    /*
//    * Provides detailed trace information
//    *
//    * @param type
//    * @param message
//    */
//    #define UR_TRACE(type, message, ...) Logger::instance().consolePrint(Core::LogLevel::TRACE, type, message, __VA_ARGS__)
//
//    /*
//    * A warning occurred, but the program can continue
//    *
//    * @param type
//    * @param message
//    */
//    #define UR_WARN(type, message, ...)  Logger::instance().consolePrint(Core::LogLevel::WARN, type, message, __VA_ARGS__)
//    
//    /*
//    * This is evaluated at run-time
//    * 
//    * @param condition - establishes if it should do an assert
//    * @param message   - displays the message of the assertion
//    */
//    #define UR_ASSERT(condition, type, message) \
//    {                                           \
//        if (condition) {                        \
//            Core::UR_ERROR(type, message);      \
//            UR_DEBUG_BREAK();                   \
//        }                                       \
//    }                                           \
//
//    /*
//    * This is evaluated at compile-time
//    * 
//    * @param condition - establishes if it should do an assert
//    * @param message   - displays the message of the assertion
//    */
//    #define UR_STATIC_ASSERT(condition, message) \
//    {                                            \
//        static_assert(condition, message);       \
//    }                                            \
//
//#elif defined(UR_RELEASE)
//    /*
//    * An error occurred. The program may need to handle this.
//    * Writes to a log file the error.
//    * 
//    * @param type
//    * @param message
//    */
//    #define UR_ERROR(type, message, ...) Logger::instance().filePrint(Core::LogLevel::ERROR, type, message, __VA_ARGS__)
//
//    /*
//    * Application cannot continue, must close program entirely
//    * Writes to a log file the fatal error.
//    *
//    * @param type
//    * @param message
//    */
//    #define UR_FATAL(type, message, ...) Logger::instance().filePrint(Core::LogLevel::FATAL, type, message, __VA_ARGS__)
//
//    #define UR_INFO(type,  message, ...)  Logger::instance().filePrint(Core::LogLevel::INFO, type, message, __VA_ARGS__)
//    #define UR_TRACE(type, message, ...)  /*Nothing*/
//    #define UR_WARN(type,  message, ...)  /*Nothing*/
//
//    #define UR_ASSERT(condition, type,  message)
//    #define UR_STATIC_ASSERT(condition, message)
//
//#elif defined(UR_DISTRIBUTION)
//    /*
//    * An error occurred. The program may need to handle this.
//    * Writes to a log file the error.
//    * 
//    * @param type
//    * @param message
//    */
//    #define UR_ERROR(type, message, ...) Logger::instance().filePrint(Core::LogLevel::ERROR, type, message, __VA_ARGS__)
//
//    /*
//    * Application cannot continue, must close program entirely
//    * Writes to a log file the fatal error.
//    *
//    * @param type
//    * @param message
//    */
//    #define UR_FATAL(type, message, ...) Logger::instance().filePrint(Core::LogLevel::FATAL, type, message, __VA_ARGS__)
//
//    #define UR_INFO(type,  message, ...)  /*Nothing*/
//    #define UR_TRACE(type, message, ...)  /*Nothing*/
//    #define UR_WARN(type,  message, ...)  /*Nothing*/
//
//    #define UR_ASSERT(condition, type, message)  /*Nothing*/
//    #define UR_STATIC_ASSERT(condition, message) /*Nothing*/
//
//#else
//    #error No build configuration defined. Must be Debug, Release, Distribution.
//#endif
//}