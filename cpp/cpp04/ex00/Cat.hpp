#pragma once

#include "Animal.hpp"

class Cat: public Animal
{

public:
    //Constructors
    Cat();
    Cat( const Cat& other );

    //Destructors
    ~Cat();

    //Overloaded operators
    Cat& operator=( const Cat& other );

    //Other methods
    void makeSound() const;

};