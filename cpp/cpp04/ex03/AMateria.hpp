#pragma once

#include <iostream>
class ICharacter;

class AMateria
{
    static AMateria* allmateria[100];
    AMateria(); //never used

protected:
    std::string _type;
    bool        _istaken;
    int         _idx;

public:
    //public constructors
    AMateria( const std::string& type );
    AMateria( const AMateria& other );

    //Destructors
    virtual ~AMateria();

    //Overloaded operators
    AMateria& operator=( const AMateria& other );

    //Other methods
    const std::string& getType() const;
    bool checkIfTaken() const;
    void setIsTaken( bool val );
    virtual AMateria* clone() const = 0;
    virtual void use( ICharacter& target );
    static void cleanup();
};