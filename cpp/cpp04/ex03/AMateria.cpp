#include "AMateria.hpp"

AMateria::AMateria()
{
    std::cout << "AMateria default constructor is called" << std::endl;
}

AMateria::AMateria( const AMateria& other ) : _type(other._type)
{
    std::cout << "AMateria copy constructor is called" << std::endl;
}

AMateria::AMateria( std::string const& type ) : _type(type)
{
    std::cout << "AMateria parametrized constructor is called" << std::endl;
}

AMateria::~AMateria() 
{
    std::cout << "AMateria destructor is called" << std::endl;
}

AMateria& AMateria::operator=( const AMateria& other )
{
    if (this == &other)
        return (*this);
    _type = other._type;
    return (*this);
}

std::string const& AMateria::getType() const
{
    return (_type);
}

void AMateria::use( ICharacter& target )
{
    (void)target;
    std::cout << "Cannot use an abstract materia.." << std::endl;
}
