#pragma once
#include <string>

class Contact
{
    public:
        std::string first_name, last_name, nickname, phone, secret;
        Contact(); // Constructor
        ~Contact() {};
        //Contact (const Contact& c);
        //Contact & operator = (const Contact& c);
};