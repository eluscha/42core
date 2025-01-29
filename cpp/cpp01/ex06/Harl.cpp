
#include "Harl.hpp"

Harl::Harl() {}

Harl::~Harl() {}

void Harl::debug( void )
{
    std::cout << "[ DEBUG ]" << std::endl;
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-";
    std::cout << "specialketchup burger. I really do!\n" << std::endl;
}
void Harl::info( void )
{
    std::cout << "[ INFO ]" << std::endl;
    std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough ";
    std::cout << "bacon in my burger! If you did, I wouldn’t be asking for more!\n" << std::endl;
}

void Harl::warning( void )
{
    std::cout << "[ WARNING ]" << std::endl;
    std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming ";
    std::cout << "for years whereas you started working here since last month.\n" << std::endl;
}

void Harl::error( void )
{
    std::cout << "[ ERROR ]" << std::endl;
    std::cout << "This is unacceptable! I want to speak to the manager now.\n" << std::endl;
}

void Harl::complain( std::string level )
{
    switch(get_index(level))
    {
        case DEBUG:     debug();
        case INFO:      info();
        case WARNING:   warning();
        case ERROR:     error(); break;
        default:        
            std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
    }
}

enum e_level get_index( std::string level )
{
    if (level == "DEBUG")
        return DEBUG;
    if (level == "INFO")
        return INFO;
    if (level == "WARNING")
        return WARNING;
    if (level == "ERROR")
        return ERROR;
    return INVALID;
}