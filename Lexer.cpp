#ifdef _WIN32
#include <io.h>
#define access _access_s
#else
#include <unistd.h>
#endif
#include "FileError.cpp"
#include "TabulationError.cpp"
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
        std::string temp, toParse;
        SyntaxTreeNode *ns = new SyntaxTreeNode();
        int lastSpaceCount = 0, spaceCount = 0, spaceCountDiff = 0;
        int lineN = 0;
        int ci = 0, i = 0;
        Token t;
        for (std::string line; getline(input, line);)
        {
            // TODO multiline, singleline comments, strings and parenthesis must be accounted for

            if (StringUtils::countOccurrenceAtStart(line, '\t') != 0)
            {
                TabulationError te(std::string("Il file \"") + fn + std::string("\" a riga ") + std::to_string(lineN + 1) + std::string(" contiene caratteri di tabulazione per indentare il codice:\n è permesso solo usare 4 spazi per ogni livello di indentazione logica."));
                throw te;
            }
            spaceCount = StringUtils::countOccurrenceAtStart(line, ' ');
            if (spaceCount % 4 != 0)
            {
                // error spaces
            }
            spaceCountDiff = (spaceCount - lastSpaceCount) / 4;
            if (spaceCountDiff > 1)
            {
                // error out, one indent at a time
            }
            else if (spaceCountDiff < 0)
            {
                for (i = 0; i < spaceCountDiff * -1; i++)
                {
                    ns = ns->parent;
                }
            }
            else if (spaceCountDiff == 1)
            {
                ns = ns->addChild(0);
            }
            for (ci = spaceCount; ci < line.length(); ci++)
            {
                temp += line[ci];
                if (ci + 1 < line.length() && !std::isspace(line[ci + 1]) && line[ci + 1] != '\n')
                {
                    continue;
                }
                toParse = StringUtils::trim_copy(temp);
                if (t.matches(toParse) > -1)
                {
                    Logger::info("Found token " + toParse);
                }
                temp = " ";
            }
            temp = "";
            // loop spaces, if find tab error out, find indentation changes
            std::cout << line << std::endl; // add chars and compare to dict
            lineN++;
            lastSpaceCount = spaceCount;
        }
    }
};