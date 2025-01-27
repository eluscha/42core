

#include "Zombie.hpp"

Zombie::Zombie() : _name("Unnamed") {}

Zombie::Zombie( std::string nm ) : _name(nm) {}

void Zombie::set_name( std::string nm) 
{
    _name = nm;
}

void Zombie::announce( void )
{
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie::~Zombie()
{
    std::cout << _name << " was destroyed!" << std::endl;
}
