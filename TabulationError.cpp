struct TabulationError : public std::exception
{
public:
    std::string message;
    TabulationError(std::string m)
    {
        message = m;
    }
    const char *what() const throw()
    {
        return message.c_str();
    }
};