
#include "Harl.hpp"

Harl::Harl() 
{
    for (int i = 0; i < 10; i++)
    {
        levelTable[i].name = "";
        levelTable[i].funcptr = &Harl::nop;
    }
    levelTable[9].name = "DEBUG";
    levelTable[9].funcptr = &Harl::debug;
    levelTable[2].name = "INFO";
    levelTable[2].funcptr = &Harl::info;
    levelTable[3].name = "WARNING";
    levelTable[3].funcptr = &Harl::warning;
    levelTable[4].name = "ERROR";
    levelTable[4].funcptr = &Harl::error;
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

void Harl::nop( void ) {}

void Harl::complain( std::string level )
{
    unsigned int hash = 0;
    for (int i = 0; i < 5; i++)
        hash = level[i] + (hash << 6) + (hash << 16) - hash; //sdbm
    hash %= 10;
    (this->*(levelTable[hash].funcptr))();
    //if (level == levelTable[hash].name)
    //    (this->*(levelTable[hash].funcptr))();
}
