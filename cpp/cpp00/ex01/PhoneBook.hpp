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

std::string check_phone(std::string ph);
int numdigits(int n);
void short_data(std::string data);
int get_idx(std::string input);
void full_data(Contact c);
