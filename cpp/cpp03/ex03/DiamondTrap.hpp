#pragma once

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap: public ScavTrap, public FragTrap
{
    std::string _name;

    using FragTrap::_hit_pts;
    using ScavTrap::_en_pts;
    using FragTrap::_attack_dmg;

public:
    
    //Constructors
    DiamondTrap();
    DiamondTrap( std::string name );
    DiamondTrap( const DiamondTrap& other );

    //Destructors
    ~DiamondTrap();

    //Overloaded operators
    // ....

    //Other methods
    using ScavTrap::attack;
    void whoAmI();

};