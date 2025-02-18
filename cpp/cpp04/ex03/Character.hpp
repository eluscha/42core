#pragma once

#include "ICharacter.hpp"

class Character : public ICharacter
{

    std::string _name;
    AMateria* _slot[4];

public:

    //Constructors
    Character();
    Character( std::string const& name );
    Character( const Character& other );

    //Destructors
    ~Character();

    //Overloaded operators
    Character& operator=( const Character& other );

    //Interface methods
    std::string const& getName() const;
    void equip( AMateria* m );
    void unequip( int idx );
    void use( int idx, ICharacter& target );

};