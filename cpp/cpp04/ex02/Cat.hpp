#pragma once

#include "AAnimal.hpp"
#include "Brain.hpp"

class Cat: public Animal
{

    Brain* _brain;

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
    Brain* getBrain() const;
};