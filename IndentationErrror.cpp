
/**
 * @file IndentationErrror.cpp
 * @brief Indentation error
 *
 * @copyright 2022, GPL-3.0
 */

/**
 * @brief Indentation error,
 *
 */
struct IndentationErrror : public std::exception
{
public:
    std::string message;
    IndentationErrror(std::string m)
    {
        message = m;
    }
    const char *what() const throw()
    {
        return message.c_str();
    }
};