#include "AAnimal.hpp"

//Constructors
AAnimal::AAnimal() : _type("none")
{
    std::cout << "AAnimal default constructor called" << std::endl;
}

AAnimal::AAnimal( std::string type ) : _type(type)
{
    std::cout << "AAnimal parameterized constructor called" << std::endl;
}

AAnimal::AAnimal( const AAnimal& other ) : _type(other._type)
{
    std::cout << "AAnimal copy constructor called" << std::endl;
}

//Destructors
AAnimal::~AAnimal()
{
    std::cout << "AAnimal destructor called" << std::endl;
}

//Overloaded operators
AAnimal& AAnimal::operator=( const AAnimal& other )
{
    std::cout << "AAnimal operator= called" << std::endl;
    if (this == &other)
        return (*this);
    _type = other._type;
    return (*this);
}

//Other methods
void AAnimal::makeSound() const 
{
    std::cout << "..." << std::endl;
}

const std::string& AAnimal::getType() const
{
    return(_type);
}