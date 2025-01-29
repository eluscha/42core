
#include "Harl.hpp"

Harl::Harl() 
{
    levelTable[0].name = "DEBUG";
    levelTable[0].funcptr = &Harl::debug;
    levelTable[1].name = "INFO";
    levelTable[1].funcptr = &Harl::info;
    levelTable[2].name = "WARNING";
    levelTable[2].funcptr = &Harl::warning;
    levelTable[3].name = "ERROR";
    levelTable[3].funcptr = &Harl::error;
}

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
    for (size_t i = 0; i < sizeof(levelTable) / sizeof(t_level); ++i)
    {
        if (level != levelTable[i].name)
            continue;
        (this->*(levelTable[i].funcptr))();
        return ;
    }
    std::cerr << "Invalid level of complaint. Enter DEBUG, INFO, WARNING, or ERROR." << std::endl;
}
