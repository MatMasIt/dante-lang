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
};