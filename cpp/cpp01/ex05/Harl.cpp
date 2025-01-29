
#include "Harl.hpp"

Harl::t_level Harl::levelTable[] = 
{
    {"DEBUG", &Harl::debug},
    {"INFO", &Harl::info},
    {"WARNING", &Harl::warning},
    {"ERROR", &Harl::error}
};

Harl::Harl() {}
Harl::~Harl() {}

void Harl::debug( void )
{
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-";
    std::cout << "specialketchup burger. I really do!" << std::endl;
}
void Harl::info( void )
{
    std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough ";
    std::cout << "bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning( void )
{
    std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming ";
    std::cout << "for years whereas you started working here since last month." << std::endl;
}

void Harl::error( void )
{
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain( std::string level )
{
    for (size_t i = 0; i < sizeof(levelTable) / sizeof(t_level); ++i)
    {
        if (level != levelTable[i].name)
            continue;
        (this->*(levelTable[i].funcptr))();
        return ;
    }
    std::cerr << "Invalid level of complaint. Enter DEBUG, INFO, WARNING, or ERROR." << std::endl;
}
