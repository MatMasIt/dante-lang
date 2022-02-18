#ifdef _WIN32
#include <io.h>
#define access _access_s
#else
#include <unistd.h>
#endif
#include "FileError.cpp"
#include "StringUtils.cpp"
class Lexer
{
public:
    SyntaxTreeNode lexFile(std::string fn)
    {
        if (!access(fn.c_str(), 0) == 0)
        {
            FileError fe(fn);
            throw fe;
        }
        if (!StringUtils::endsWith(fn, ".dante"))
            Logger::warning("L'estensione del file specificato non coincide con \".dante\"");
        std::ifstream input(fn);
        std::string temp;
        for (std::string line; getline(input, line);)
        {
            std::cout << line << std::endl; // add chars and compare to dict
        }
    }
};