#include "WrongAnimal.hpp"

//Constructors
WrongAnimal::WrongAnimal() : _type("none")
{
    std::cout << "WrongAnimal default constructor called" << std::endl;
}

WrongAnimal::WrongAnimal( std::string type ) : _type(type)
{
    std::cout << "WrongAnimal parameterized constructor called" << std::endl;
}

WrongAnimal::WrongAnimal( const WrongAnimal& other ) : _type(other._type)
{
    std::cout << "WrongAnimal copy constructor called" << std::endl;
}

//Destructors
WrongAnimal::~WrongAnimal()
{
    std::cout << "WrongAnimal destructor called" << std::endl;
}

//Overloaded operators
WrongAnimal& WrongAnimal::operator=( const WrongAnimal& other )
{
    std::cout << "WrongAnimal operator= called" << std::endl;
    if (this == &other)
        return (*this);
    _type = other._type;
    return (*this);
}

//Other methods
void WrongAnimal::makeSound() const
{
    std::cout << "[generic animal sound...]" << std::endl;
}

const std::string& WrongAnimal::getType() const
{
    return(_type);
}