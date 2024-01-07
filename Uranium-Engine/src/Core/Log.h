#include <string>

#ifdef UR_DEBUG
#include <iostream>
#endif // UR_DEBUG

namespace Uranium::Core {

    enum class LogLevel {
        Debug,
        Info,
        Warning,
        Error
    };

    class Logger final {
    public:
        enum class TextColor {
            BLACK,
            RED,
            Green,
            Yellow,
            Blue,
            Magenta,
            Cyan,
            White,
            Count
        };

        static const char* colorCodes[static_cast<uint32_t>(TextColor::Count)] = {
            "\033[0;30m",  // Black
            "\033[0;31m",  // Red
            "\033[0;32m",  // Green
            "\033[0;33m",  // Yellow
            "\033[0;34m",  // Blue
            "\033[0;35m",  // Magenta
            "\033[0;36m",  // Cyan
            "\033[0;37m"   // White
        };
        explicit Logger(const std::string& logFileName) noexcept;

        ~Logger();

    public:
        /*
        */
        static void print(Logger& logger, const std::string& message);

        static void print(
            TextColor headerColor,
            TextColor messageColor,
            const std::string& header,
            const std::string& message
        ) {
            const char* headerColorCode = Logger::colorCodes[static_cast<uint32_t>(headerColor)];
            const char* messageColorCode = Logger::colorCodes[static_cast<uint32_t>(messageColor)];

            std::cout << headerColorCode << "[" << header << "] " <<
            colorCodes[static_cast<uint32_t>(TextColor::White)]   <<
            messageColorCode                                      <<
            message                                               << 
            colorCodes[static_cast<uint32_t>(TextColor::White)]   <<
            std::endl;
        }

    private:
        std::string logFileName;

    };

#ifdef UR_DEBUG
#define UR_TRACE(message)

#endif // UR_DEBUG

}
