#pragma once

#include "AMateria.hpp"

class Ice : public AMateria
{
public:
    //Constructors
    Ice();
    Ice( const Ice& other );

    //Destructors
    virtual ~Ice();

    //Overloaded operators
    Ice& operator=( const Ice& other );

    //Other methods
    
};