#include "HumanA.hpp"

HumanA::HumanA( std::string nm, Weapon& wp ) : _name(nm), _weapon(wp) {};

std::string HumanA::getName( void )
{
    return (_name);
}
Weapon HumanA::getWeapon( void )
{
    return (_weapon);
}

void HumanA::attack( void )
{
    std::cout << _name << " attacks with their " << _weapon.getType() << std::endl;
}

