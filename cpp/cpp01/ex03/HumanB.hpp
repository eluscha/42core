
#pragma once
#include <iostream>
#include "Weapon.hpp"

class HumanB
{
    std::string _name;
    Weapon* _weapon;

public:

    HumanB( std::string nm );

    std::string getName( void );
    Weapon getWeapon( void );
    void setWeapon( Weapon& wp );
    void attack();
};

