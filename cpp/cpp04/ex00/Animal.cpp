#include "Animal.hpp"

//Constructors
Animal::Animal() : _type("none")
{
    std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal( std::string type ) : _type(type)
{
    std::cout << "Animal parameterized constructor called" << std::endl;
}

Animal::Animal( const Animal& other ) : _type(other._type)
{
    std::cout << "Animal copy constructor called" << std::endl;
}

//Destructors
Animal::~Animal()
{
    std::cout << "Animal destructor called" << std::endl;
}

//Overloaded operators
Animal& Animal::operator=( const Animal& other )
{
    std::cout << "Animal operator= called" << std::endl;
    if (this == &other)
        return (*this);
    _type = other._type;
    return (*this);
}

//Other methods
void Animal::makeSound() const
{
    std::cout << "[generic animal sound...]" << std::endl;
}

const std::string& Animal::getType() const
{
    return(_type);
}