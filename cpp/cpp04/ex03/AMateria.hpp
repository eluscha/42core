#pragma once

#include <string>
#include "ICharacter.hpp"

class AMateria
{
protected:
    std::string type;

    AMateria();
    AMateria( const AMateria& other );

public:
    //parametrized constructor
    AMateria( std::string const& type );

    //Destructors
    ~AMateria();

    //Overloaded operators
    AMateria& operator=( const AMateria& other );

    std::string const& getType() const; //Returns the materia type

    virtual AMateria* clone() const = 0;
    virtual void use(ICharacter& target);
};