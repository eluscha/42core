
#include "mysed.hpp"

std::string edit_line(std::string line, std::string s1, std::string s2)
{
    if (s1 == s2)
        return (line);
    size_t last_pos = 0;
    size_t pos = line.find(s1, last_pos);
    std::string ret;
    while (pos != std::string::npos)
    {
        ret += line.substr(last_pos, pos - last_pos);
        ret += s2;
        last_pos = pos + s1.length();
        pos = line.find(s1, last_pos);
    }
    ret += line.substr(last_pos);
    return (ret);
}