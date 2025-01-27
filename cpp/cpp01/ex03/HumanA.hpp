
#pragma once
#include <iostream>
#include "Weapon.hpp"

class HumanA
{
    std::string _name;
    Weapon& _weapon;

public:

    HumanA( std::string nm, Weapon& wp );

    std::string getName( void );
    Weapon getWeapon( void );

    void attack();
};

