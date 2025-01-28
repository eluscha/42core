
#include <iostream>
#include <string>
#include <fstream>

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

int main( int argc, char** argv ) 
{
    if (argc != 4)
        return (1);
    std::string filename = argv[1];
    std::string s1 = argv[2];
    if (!s1.length())
    {
        std::cerr << "A string to be replaced cannot be empty" << std::endl;
        return (1);
    }
    std::string s2 = argv[3];
    std::ifstream from(filename.c_str(), std::ios::in);
    if (!from.is_open())
    {
        std::cerr << "Failed to open for reading: " << filename << std::endl;
        return (1);
    }

    std::ofstream to((filename + ".replace").c_str(), std::ios::out);
    if (!to.is_open())
    {
        from.close();
        std::cerr << "Failed to open for writing: " << filename << ".replace" << std::endl;
        return (1);
    }

    std::string line;
    while (std::getline(from, line))
    {
        to << edit_line(line, s1, s2);
        if (!from.eof())
            to << std::endl;
    }
    from.close();
    to.close();
}
