#include <iostream>
#include "Contact.hpp"
#include "PhoneBook.hpp"

int main(void)
{
    PhoneBook phonebook;
    phonebook.listen();
    std::cout << phonebook.list[0].first_name << std::endl;
}