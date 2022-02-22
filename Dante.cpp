#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include "portability.cpp"
#include "Logger.cpp"
#include "SyntaxTreeNode.cpp"
#include "Lexer.cpp"
#include "Executer.cpp"
class Dante
{
public:
    std::vector<std::string> fileNameList;
    std::vector<SyntaxTreeNode> mainSyntaxTreeList;
    Lexer lexE;
    Executer exec;
    Dante(std::vector<std::string> fnl)
    {
        fileNameList = fnl;
    }
    void lex()
    {
        for (std::vector<std::string>::iterator t = fileNameList.begin(); t != fileNameList.end(); ++t)
        {
            auto start = std::chrono::high_resolution_clock::now();
            //std::this_thread::sleep_for(std::chrono::milliseconds(10000));

            mainSyntaxTreeList.push_back(lexE.lexFile(*t));
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            Logger::debug(*t + std::string(", analisi lessicale: ") + std::to_string(duration.count()) + std::string("μs"));
        }
    }
    void execute()
    {
        for (std::vector<SyntaxTreeNode>::iterator s = mainSyntaxTreeList.begin(); s != mainSyntaxTreeList.end(); ++s)
        {

            exec.exec(*s);
        }
    }
};

int main(int argc, char *argv[], char *envp[])
{
    if (argc < 2)
    {
        Logger::error("Occorre specificare almeno un programma da eseguire");
        return 1;
    }
    std::vector<std::string> fileNameList = std::vector<std::string>();
    for (int i = 1; i < argc; i++)
    {
        std::string str(argv[i]);
        fileNameList.push_back(str);
    }
    Dante d(fileNameList);
    try
    {
        d.lex();
    }
    catch (FileError &ex)
    {
        Logger::error("Il file  \"" + std::string(ex.what()) + "\" non esiste o non è accessibile");
        return 1;
    }
    catch (TabulationError &ex)
    {
        Logger::error(std::string(ex.what()));
        return 1;
    }
    d.execute();
    return 0;
}
