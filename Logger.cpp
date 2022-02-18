
#include "rlutil.h"
class Logger
{
public:
    static void error(std::string message)
    {
        rlutil::setColor(rlutil::RED);
        std::cerr << "Errore: ";
        rlutil::setColor(rlutil::WHITE);
        std::cerr << message << std::endl;
    }
    static void info(std::string message)
    {
        rlutil::setColor(rlutil::BLUE);
        std::cerr << "Info: ";
        rlutil::setColor(rlutil::WHITE);
        std::cerr << message << std::endl;
    }
    static void warning(std::string message)
    {
        rlutil::setColor(rlutil::YELLOW);
        std::cerr << "Avvertimento: ";
        rlutil::setColor(rlutil::WHITE);
        std::cerr << message << std::endl;
    }
};