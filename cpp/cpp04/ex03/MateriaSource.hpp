#pragma once

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
    AMateria* _slot[4];

public:
    //Constructors
    MateriaSource();
    MateriaSource( const std::string& name );
    MateriaSource( const MateriaSource& other );

    //Destructors
    ~MateriaSource();

    //Overloaded operators
    MateriaSource& operator=( const MateriaSource& other );

    //Interface methods
    void learnMateria( AMateria* );
    AMateria* createMateria( const std::string& type );

};