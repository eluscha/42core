#include "WrongCat.hpp"

//Constructors
WrongCat::WrongCat() : WrongAnimal("WrongCat")
{
    std::cout << "WrongCat default constructor called" << std::endl;
}
WrongCat::WrongCat( const WrongCat& other ) : WrongAnimal(other)
{
    std::cout << "WrongCat copy constructor called" << std::endl;
}

//Destructors
WrongCat::~WrongCat()
{
    std::cout << "WrongCat destructor called" << std::endl;
}

//Overloaded operators
WrongCat& WrongCat::operator=( const WrongCat& other )
{
    std::cout << "WrongCat operator= called" << std::endl;
    if (this == &other)
        return (*this);
    _type = other._type;
    return (*this);
}

//Other methods
void WrongCat::makeSound() const
{
    std::cout << "Meow meow prrrr" << std::endl;
}