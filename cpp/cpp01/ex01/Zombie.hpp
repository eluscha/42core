
#pragma once
#include <iostream>
#include <string>

class Zombie 
{
    std::string _name;

public:

    Zombie();
    Zombie( std::string nm );

    void set_name( std::string nm );
    void announce( void );

    ~Zombie();
    
};

Zombie* zombieHorde( int N, std::string name );