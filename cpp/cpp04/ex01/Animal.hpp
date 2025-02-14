#pragma once

#include <string>
#include <iostream>

class Animal
{

protected:
    std::string _type;

public:
    //Constructors
    Animal();
    Animal( std::string type );
    Animal( const Animal& other );

    //Destructors
    virtual ~Animal();

    //Overloaded operators
    Animal& operator=( const Animal& other );

    //Other methods
    virtual void makeSound() const;
    const std::string& getType() const;

};