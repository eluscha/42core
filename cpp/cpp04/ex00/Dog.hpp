#pragma once

#include "Animal.hpp"

class Dog: public Animal
{

public:
    //Constructors
    Dog();
    Dog( const Dog& other );

    //Destructors
    ~Dog();

    //Overloaded operators
    Dog& operator=( const Dog& other );

    //Other methods
    void makeSound() const;

};