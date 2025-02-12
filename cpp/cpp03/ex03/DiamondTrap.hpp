#pragma once

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap: public ScavTrap, public FragTrap
{
    std::string _name;

public:
    
    //Constructors
    DiamondTrap();
    DiamondTrap( std::string name );
    DiamondTrap( const DiamondTrap& other );

    //Destructors
    ~DiamondTrap();

    //Overloaded operators
    DiamondTrap& operator=( const DiamondTrap& other );

    //Other methods
    using ScavTrap::attack;
    void whoAmI();

    //Getters
    int getHitPts();
    int getEnPts();

};