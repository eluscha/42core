#pragma once
#include <iostream>
#include "Contact.hpp"

class PhoneBook
{

    public:
        Contact list[8];
        int size; 
        PhoneBook();
        //PhoneBook (const PhoneBook &c);
        //PhoneBook & operator = (const PhoneBook &c);

        void listen();
        void add();
        void search(void);
        void exit(void); 
};