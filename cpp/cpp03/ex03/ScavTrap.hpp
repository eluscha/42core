#pragma once
#include "ClapTrap.hpp"

class  ScavTrap : virtual public ClapTrap
{

protected:
    bool _gateKeeper;

public:
        // Constructors
		ScavTrap();
        ScavTrap( std::string name );
		ScavTrap( const ScavTrap& other );

        //Destructors
        ~ScavTrap();

        //Overloaded operators
        ScavTrap& operator=( const ScavTrap& other );

        //Other methods
        void attack( const std::string& target );
        void guardGate();

        int getEnPts();
};