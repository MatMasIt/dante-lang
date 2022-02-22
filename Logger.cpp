class Logger
{
public:
    static void error(std::string message)
    {
        fmt::print("{}: {} \n", format(fmt::emphasis::bold | fg(fmt::color::red), "Errore"), message);
    }
    static void info(std::string message)
    {
        fmt::print("{}: {} \n", format(fmt::emphasis::bold | fg(fmt::color::blue), "Info"), message);
    }
    static void warning(std::string message)
    {
        fmt::print("{}: {} \n", format(fmt::emphasis::bold | fg(fmt::color::orange), "Avvertimento"),  message);
    }
    static void debug(std::string message)
    {
        fmt::print("{}: {} \n", format(fmt::emphasis::bold | fg(fmt::color::magenta), "Interno"),  message);

    }
};
