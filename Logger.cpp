/**
 * @brief Logger utilities
 *
 */
class Logger
{
public:
    /**
     * @brief Log error
     *
     * @param message message to log
     */
    static void error(std::string message)
    {
        fmt::print("{}: {} \n", format(fmt::emphasis::bold | fg(fmt::color::red), "Errore"), message);
    }
    /**
     * @brief Log info
     *
     * @param message message to log
     */
    static void info(std::string message)
    {
        fmt::print("{}: {} \n", format(fmt::emphasis::bold | fg(fmt::color::blue), "Info"), message);
    }
    /**
     * @brief Log warning
     *
     * @param message message to log
     */
    static void warning(std::string message)
    {
        fmt::print("{}: {} \n", format(fmt::emphasis::bold | fg(fmt::color::orange), "Avvertimento"), message);
    }
    /**
     * @brief Log debugging message
     *
     * @param message message to log
     */
    static void debug(std::string message)
    {
        fmt::print("{}: {} \n", format(fmt::emphasis::bold | fg(fmt::color::magenta), "Interno"), message);
    }
};
