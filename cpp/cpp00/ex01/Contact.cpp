#include "Contact.hpp"

Contact::Contact(std::string fn, std::string ln, std::string nn, std::string ph, std::string sc)
    : first_name(fn), last_name(ln), nickname(nn), phone(ph), secret(sc) {}

std::string Contact::get_first_name()
{
    return first_name;
}

std::string Contact::get_last_name()
{
    return last_name;
}

std::string Contact::get_nickname()
{
    return nickname;
}

std::string Contact::get_phone()
{
    return phone;
}
std::string Contact::get_secret()
{
    return secret;
}