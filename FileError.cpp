
/**
 * @file FileError.cpp
 * @brief File access error
 *
 * @copyright 2022, GPL-3.0
 */

/**
 * @brief File access error exception
 *
 */
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