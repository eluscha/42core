#include <iostream>
#include "Contact.hpp"
#include "PhoneBook.hpp"

int main(void)
{
    int code;
    PhoneBook phonebook;
    while (1)
    {
        code = phonebook.listen();
        if (code == 0)
            phonebook.add();
        break ;
    }
    std::cout << phonebook.list[0].first_name << std::endl;
}