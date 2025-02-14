#pragma once

#include "WrongAnimal.hpp"

class WrongCat: public WrongAnimal
{

public:
    //Constructors
    WrongCat();
    WrongCat( const WrongCat& other );

    //Destructors
    ~WrongCat();

    //Overloaded operators
    WrongCat& operator=( const WrongCat& other );

    //Other methods
    void makeSound() const;

};