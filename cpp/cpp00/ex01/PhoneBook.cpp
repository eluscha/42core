#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
    : size(0) {}

void PhoneBook::listen()
{
    std::string input;
    while (1)
    {
        std::cout << "Please enter command: ADD, SEARCH or EXIT" << std::endl;
        std::getline(std::cin, input);
        if (input == "ADD")
            add();
        else if (input == "SEARCH")
            search();
        else if (input == "EXIT")
            return (exit());
    }
}

void get_input(const std::string msg, std::string *field)
{
    while (!(*field).size())
    {
        std::cout << msg;
        std::getline(std::cin, *field);
    }
}

void PhoneBook::add()
{
    //Contact& c = list[size];
    get_input("First name: ", &list[size].first_name);
    get_input("Last name: ", &list[size].last_name);
    get_input("Nickname: ", &list[size].nickname);
    get_input("Phone (at least 5 digits): ", &list[size].phone);
    get_input("Darkest secret: ",  &list[size].secret);
    size++;
}

void PhoneBook::search()
{
    for (int i=0; i < size; i++)
    {
        std::cout << list[i].first_name << " | " << list[i].last_name << std::endl;
    }
}

void PhoneBook::exit()
{       
    for (int i=0; i < size; i++)
        list[i] = Contact();
    size = 0;
    std::cout << "BYE" << std::endl;
}