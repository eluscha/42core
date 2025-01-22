#pragma once
#include <string>

class Contact
{
    std::string first_name, last_name, nickname, phone, secret;

public:

    Contact();
    Contact(std::string fn, std::string ln, std::string nn, std::string ph, std::string sc);
    
    ~Contact() {};

    std::string get_first_name();
    std::string get_last_name();
    std::string get_nickname();
    std::string get_phone();
    std::string get_secret();

};