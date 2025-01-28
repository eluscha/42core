
#include "mysed.hpp"

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

    if (s1.find('\n') != std::string::npos)
    {
        std::stringstream buffer;
        buffer << from.rdbuf(); // Read the whole file into the stringstream
        std::string lines = buffer.str();
        to << edit_line(lines, s1, s2);
        from.close();
        to.close();
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
