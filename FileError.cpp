struct FileError : public std::exception
{
public:
    std::string filename;
    FileError(std::string fn)
    {
        filename = fn;
    }
    const char *what() const throw()
    {
        return filename.c_str();
    }
};