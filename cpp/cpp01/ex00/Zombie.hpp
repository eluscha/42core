
#pragma once
#include <iostream>

class Zombie 
{
    std::string _name;

    Zombie();

public:

    Zombie( std::string nm );
    void announce( void );

    ~Zombie();
    
};

Zombie* newZombie( std::string name );
void randomChump( std::string name );