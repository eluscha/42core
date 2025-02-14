#pragma once

#include <string>
#include <iostream>

class WrongAnimal
{

protected:
    std::string _type;

public:
    //Constructors
    WrongAnimal();
    WrongAnimal( std::string type );
    WrongAnimal( const WrongAnimal& other );

    //Destructors
    virtual ~WrongAnimal();

    //Overloaded operators
    WrongAnimal& operator=( const WrongAnimal& other );

    //Other methods
    void makeSound() const; //non virtial!
    const std::string& getType() const;

};
