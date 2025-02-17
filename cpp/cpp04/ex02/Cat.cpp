#include "Cat.hpp"

//Constructors
Cat::Cat() : AAnimal("Cat")
{
    std::cout << "Cat default constructor called" << std::endl;
    _brain = new Brain();
}
Cat::Cat( const Cat& other ) : AAnimal(other)
{
    std::cout << "Cat copy constructor called" << std::endl;
    _brain = new Brain(*other._brain);
}

//Destructors
Cat::~Cat()
{
    std::cout << "Cat destructor called" << std::endl;
    delete _brain;
}

//Overloaded operators
Cat& Cat::operator=( const Cat& other )
{
    std::cout << "Cat operator= called" << std::endl;
    if (this == &other)
        return (*this);
    _type = other._type;
    *_brain = *other._brain;
    return (*this);
}

//Other methods
void Cat::makeSound() const
{
    std::cout << "Meow meow prrrr" << std::endl;
}

Brain* Cat::getBrain() const
{
    return (_brain);
}