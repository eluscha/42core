#include "HumanB.hpp"

HumanB::HumanB( std::string nm) : _name(nm), _weapon(0) {}

std::string HumanB::getName( void )
{
    return (_name);
}
Weapon HumanB::getWeapon( void )
{
    return (*_weapon);
}

void HumanB::setWeapon(Weapon& wp)
{
    _weapon = &wp;
}

void HumanB::attack( void )
{
    if (_weapon)
        std::cout << _name << " attacks with their " << (*_weapon).getType() << std::endl;
    else
        std::cout << _name << " attacks with their bare hands" << std::endl;
}