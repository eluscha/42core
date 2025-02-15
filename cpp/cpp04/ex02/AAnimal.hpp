#pragma once

#include <string>
#include <iostream>

class Animal
{

protected:
    std::string _type;

    //Constructors
    Animal();
    Animal( std::string type );
    Animal( const Animal& other );

public:

    //Destructors
    virtual ~Animal() = 0;

    //Overloaded operators
    Animal& operator=( const Animal& other );

    //Other methods
    virtual void makeSound() const;
    const std::string& getType() const;

};