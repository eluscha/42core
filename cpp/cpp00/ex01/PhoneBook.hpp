#pragma once
#include <iostream>
#include "Contact.hpp"

class PhoneBook
{

    public:
        Contact list[8];
        int size; 
        PhoneBook() {
            size = 0;
        }
        //PhoneBook (const PhoneBook &c);
        //PhoneBook & operator = (const PhoneBook &c);

        int listen()
        {
            std::cout << "Please enter command: ADD, SEARCH or EXIT" << std::endl;
            return (0);
        }
        void add();
        //void search(void);
        //void exit(void); 
};