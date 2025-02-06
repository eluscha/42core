#pragma once
#include "ClapTrap.hpp"

class  FragTrap : virtual public ClapTrap
{

public:
        // Constructors
		FragTrap();
        FragTrap( std::string name );
		FragTrap( const FragTrap& other );

        //Destructors
        ~FragTrap();

        //Overloaded operators
        FragTrap& operator=( const FragTrap& other );

        //Other methods
        void attack( const std::string& target );
        void highFivesGuys( void );
};