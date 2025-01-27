

#include "Weapon.hpp"

Weapon::Weapon() {}

Weapon::Weapon( std::string tp ) : _type(tp) {}

std::string Weapon::getType( void )
{
    return (_type);
}

void Weapon::setType( std::string tp)
{
    _type = tp;
}

Weapon::~Weapon() {}