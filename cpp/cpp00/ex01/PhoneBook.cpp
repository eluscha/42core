#include "PhoneBook.hpp"

void PhoneBook::add()
{
    std::string input;
    while (!input.size())
    {
        std::cout << "First name:";
        std::cin >> input;
        std::cout << std::endl;
    }
    list[size].first_name = input;         
    size++;
}