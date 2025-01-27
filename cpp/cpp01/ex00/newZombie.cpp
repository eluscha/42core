

#include "Zombie.hpp"

Zombie* newZombie( std::string name )
{
    Zombie* zmb = new Zombie(name); // dynamically allocated
    return zmb;
}