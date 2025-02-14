#include "Dog.hpp"

//Constructors
Dog::Dog() : Animal("Dog")
{
    std::cout << "Dog default constructor called" << std::endl;
    _brain = new Brain();
}
Dog::Dog( const Dog& other ) : Animal(other)
{
    std::cout << "Dog copy constructor called" << std::endl;
    _brain = new Brain(*other._brain);
}

//Destructors
Dog::~Dog()
{
    std::cout << "Dog destructor called" << std::endl;
    delete _brain;
}

//Overloaded operators
Dog& Dog::operator=( const Dog& other )
{
    std::cout << "Dog operator= called" << std::endl;
    if (this == &other)
        return (*this);
    _type = other._type;
    *_brain = *other._brain;
    return (*this);
}

//Other methods
void Dog::makeSound() const
{
    std::cout << "Woof woof rrrr" << std::endl;
}

Brain* Dog::getBrain() const
{
    return (_brain);
}