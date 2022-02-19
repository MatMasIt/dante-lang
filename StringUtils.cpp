#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
class StringUtils
{
public:
    static bool endsWith(const std::string &str, const std::string &suffix)
    {
        return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
    }

    static bool startsWith(const std::string &str, const std::string &prefix)
    {
        return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
    }
    static bool endsWith(const std::string &str, const char *suffix, unsigned suffixLen)
    {
        return str.size() >= suffixLen && 0 == str.compare(str.size() - suffixLen, suffixLen, suffix, suffixLen);
    }

    static bool endsWith(const std::string &str, const char *suffix)
    {
        return endsWith(str, suffix, std::string::traits_type::length(suffix));
    }

    static bool startsWith(const std::string &str, const char *prefix, unsigned prefixLen)
    {
        return str.size() >= prefixLen && 0 == str.compare(0, prefixLen, prefix, prefixLen);
    }

    static bool startsWith(const std::string &str, const char *prefix)
    {
        return startsWith(str, prefix, std::string::traits_type::length(prefix));
    }

    // trim from start (in place)
    static inline void ltrim(std::string &s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                        std::not1(std::ptr_fun<int, int>(std::isspace))));
    }

    // trim from end (in place)
    static inline void rtrim(std::string &s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(),
                             std::not1(std::ptr_fun<int, int>(std::isspace)))
                    .base(),
                s.end());
    }

    // trim from both ends (in place)
    static inline void trim(std::string &s)
    {
        ltrim(s);
        rtrim(s);
    }

    // trim from start (copying)
    static inline std::string ltrim_copy(std::string s)
    {
        ltrim(s);
        return s;
    }

    // trim from end (copying)
    static inline std::string rtrim_copy(std::string s)
    {
        rtrim(s);
        return s;
    }

    // trim from both ends (copying)
    static inline std::string trim_copy(std::string s)
    {
        trim(s);
        return s;
    }

    static inline int countOccurrenceAtStart(std::string s, char c)
    {
        int occcurrence = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] != c)
                return occcurrence;
            occcurrence++;
        }
        return occcurrence;
    }
};
