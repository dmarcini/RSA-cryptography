#ifndef PARSE_SOURCE_HPP_
#define PARSE_SOURCE_HPP_

#include <string>
#include <iostream>
#include <vector>


namespace RSA {

class SourceString
{
public:
    SourceString(const std::string &str) : str_(str) {}

    std::string path(const char delim = '=') const
    {
        return str_.substr(str_.find(delim) + 1);
    }

    bool start_with(const std::string &ctx) const
    {
        return str_.rfind(ctx, 0) != std::string::npos;
    }

    const std::string str() const
    {
        return str_;
    }
private:
    std::string str_ {};
};


enum class Option
{
    GenKeys,
    Encrypt,
    Decrypt,
    Unknow
};


Option parse_sources(int argc, const std::vector<SourceString> &sources)
{
    if (argc == 2 && sources[1].start_with("--gen-keys=")) {
        return Option::GenKeys;
    } else if (argc == 3 &&
               sources[1].start_with("--key=") &&
               sources[2].start_with("--encrypt=")) {
        return Option::Encrypt;
    } else if (argc == 3 &&
               sources[1].start_with("--key=") &&
               sources[2].start_with("--decrypt=")) {
        return Option::Decrypt;
    } else {
        return Option::Unknow;
    }
}

}; // namespace RSA

#endif // PARSE_SOURCE_HPP_

