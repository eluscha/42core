#include "Dog.hpp"

//Constructors
Dog::Dog() : Animal()
{
    std::cout << "Dog default constructor called" << std::endl;
    _type = "Dog";
}
Dog::Dog( const Dog& other ) : Animal(other)
{
    std::cout << "Dog copy constructor called" << std::endl;
}

//Destructors
Dog::~Dog()
{
    std::cout << "Dog destructor called" << std::endl;
}

//Overloaded operators
Dog& Dog::operator=( const Dog& other )
{
    std::cout << "Dog operator= called" << std::endl;
    if (this == &other)
        return (*this);
    _type = other._type;
    return (*this);
}

//Other methods
void Dog::makeSound() const
{
    std::cout << "Woof woof rrrr" << std::endl;
}