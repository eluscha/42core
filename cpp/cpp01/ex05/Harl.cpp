
#include "Harl.hpp"

Harl::Harl() 
{
    for (int i = 0; i < HASHTSIZE; i++)
        hashTable[i].funcptr = &Harl::invalid;
    hashTable[9].name = "DEBUG";
    hashTable[9].funcptr = &Harl::debug;
    hashTable[2].name = "INFO";
    hashTable[2].funcptr = &Harl::info;
    hashTable[3].name = "WARNING";
    hashTable[3].funcptr = &Harl::warning;
    hashTable[4].name = "ERROR";
    hashTable[4].funcptr = &Harl::error;
}

Harl::~Harl() {}

void Harl::debug( void )
{
    if (hashTable[9].to_check != hashTable[9].name)
        return (invalid());
    std::cout << "[ DEBUG ]" << std::endl;
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-";
    std::cout << "specialketchup burger. I really do!\n" << std::endl;
}
void Harl::info( void )
{
    if (hashTable[2].to_check != hashTable[2].name)
        return (invalid());
    std::cout << "[ INFO ]" << std::endl;
    std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough ";
    std::cout << "bacon in my burger! If you did, I wouldn’t be asking for more!\n" << std::endl;
}

void Harl::warning( void )
{
    if (hashTable[3].to_check != hashTable[3].name)
        return (invalid());
    std::cout << "[ WARNING ]" << std::endl;
    std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming ";
    std::cout << "for years whereas you started working here since last month.\n" << std::endl;
}

void Harl::error( void )
{
    if (hashTable[4].to_check != hashTable[4].name)
        return (invalid());
    std::cout << "[ ERROR ]" << std::endl;
    std::cout << "This is unacceptable! I want to speak to the manager now.\n" << std::endl;
}

void Harl::invalid( void ) 
{
    std::cerr << "Error: Invalid level of complaint." << std::endl;
}

void Harl::complain( std::string level )
{
    unsigned int hashval = 0;
    for (int i = 0; i < 5; i++)
        hashval = level[i] + (hashval << 6) + (hashval << 16) - hashval; //sdbm
    hashval %= HASHTSIZE;
    hashTable[hashval].to_check = level;
    (this->*(hashTable[hashval].funcptr))();
}
