#pragma once

#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog: public Animal
{

    Brain* _brain;

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
    Brain* getBrain() const;

};