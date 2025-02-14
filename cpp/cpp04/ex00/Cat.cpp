#include "Cat.hpp"

//Constructors
Cat::Cat() : Animal("Cat")
{
    std::cout << "Cat default constructor called" << std::endl;
}
Cat::Cat( const Cat& other ) : Animal(other)
{
    std::cout << "Cat copy constructor called" << std::endl;
}

//Destructors
Cat::~Cat()
{
    std::cout << "Cat destructor called" << std::endl;
}

//Overloaded operators
Cat& Cat::operator=( const Cat& other )
{
    std::cout << "Cat operator= called" << std::endl;
    if (this == &other)
        return (*this);
    _type = other._type;
    return (*this);
}

//Other methods
void Cat::makeSound() const
{
    std::cout << "Meow meow prrrr" << std::endl;
}