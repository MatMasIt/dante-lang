#ifdef _WIN32
#include <io.h>
#define access _access_s
#else
#include <unistd.h>
#endif
#include "FileError.cpp"
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
        std::ifstream input(fn);
    }
};