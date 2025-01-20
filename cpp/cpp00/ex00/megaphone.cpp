#include <iostream>

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
        return (0);
    }
    int i = 0;
    while (++i < argc)
    {
        std::string input = argv[i];
        for (std::string::size_type j = 0; j < input.size(); j++)
            input[j] = toupper(input[j]);
        std::cout << input;
    }
    std::cout << std::endl;
    return (0);
}