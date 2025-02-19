#include "AMateria.hpp"

AMateria* AMateria::allmateria[100] = {NULL};

AMateria::AMateria() 
{
    std::cout << "AMateria default constructor is called" << std::endl;
}

AMateria::AMateria( const AMateria& other ) : _type(other._type), _istaken(false)
{
    //std::cout << "AMateria copy constructor is called" << std::endl;
    for (int i = 0; i < 100; i++)
    {
        if (!allmateria[i])
        {
            allmateria[i] = this;
            _idx = i;
            break;
        }
        else if (i == 99)
        {
            std::cerr << "Cannot store more than 100 objects in the allmateria array!";
            std::cerr << "Memory leaks possible for an obj at " << this << std::endl;
            _idx = -1;
        }
    }
}

AMateria::AMateria( std::string const& type ) : _type(type), _istaken(false)
{
    //std::cout << "AMateria parametrized constructor is called" << std::endl;
    for (int i = 0; i < 100; i++)
    {
        if (!allmateria[i])
        {
            allmateria[i] = this;
            _idx = i;
            break;
        }
        else if (i == 99)
        {
            std::cerr << "Cannot store more than 100 objects in the allmateria array!";
            std::cerr << "Memory leaks possible for an obj at " << this << std::endl;
            _idx = -1;
        }
    }
}

AMateria::~AMateria() 
{
    //std::cout << "AMateria destructor is called" << std::endl;
    if (_idx >= 0 && _idx < 100)
        allmateria[_idx] = NULL;
}

AMateria& AMateria::operator=( const AMateria& other )
{
    //std::cout << "AMateria =operator is called" << std::endl;
    if (this == &other)
        return (*this);
    //We are told to not copy the _type. I would overall forbid assignemnt when types are different.
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

bool AMateria::checkIfTaken() const
{
    return (_istaken);
}

void AMateria::setIsTaken( bool val )
{
    _istaken = val;
}

void AMateria::cleanup()
{
    for (int i = 0; i < 100; i++)
    {
        if (allmateria[i])
        {
            delete allmateria[i];
            allmateria[i] = NULL;
        }
    }
}