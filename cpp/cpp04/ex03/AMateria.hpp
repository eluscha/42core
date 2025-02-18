#pragma once

#include <iostream>
class ICharacter;

class AMateria
{
protected:
    std::string _type;

    AMateria();
    AMateria( const AMateria& other );

public:
    //parametrized constructor
    AMateria( std::string const& type );

    //Destructors
    virtual ~AMateria();

    //Overloaded operators
    AMateria& operator=( const AMateria& other );

    //Other methods
    std::string const& getType() const;

    virtual AMateria* clone() const = 0;
    virtual void use( ICharacter& target );
};