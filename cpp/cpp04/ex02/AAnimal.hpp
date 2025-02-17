#pragma once

#include <string>
#include <iostream>

class AAnimal
{

protected:
    std::string _type;

    //Constructors
    AAnimal();
    AAnimal( std::string type );
    AAnimal( const AAnimal& other );

public:

    //Destructors
    virtual ~AAnimal();

    //Overloaded operators
    AAnimal& operator=( const AAnimal& other );

    //Other methods
    virtual void makeSound() const = 0; //pure virtual
    const std::string& getType() const;

};