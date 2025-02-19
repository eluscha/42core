#include "MateriaSource.hpp"

//Constructors
MateriaSource::MateriaSource()
{
    //std::cout << "MateriaSource default constructor is called" << std::endl;
    for (int i = 0; i < 4; i++)
        _slot[i] = NULL;
}

MateriaSource::MateriaSource( const MateriaSource& other )
{
    //std::cout << "MateriaSource copy constructor is called" << std::endl;
    *this = other;
}

//Destructors
MateriaSource::~MateriaSource()
{
    //std::cout << "MateriaSource destructor is called" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        if (_slot[i])
            delete _slot[i];
    }
}

//Overloaded operators
MateriaSource& MateriaSource::operator=( const MateriaSource& other )
{
    if (this == &other)
        return (*this);
    for (int i = 0; i < 4; i++)
    {
        if (_slot[i])
        {
            delete _slot[i];
            _slot[i] = NULL;
        }
        if (!other._slot[i])
            continue ;
        _slot[i] = other._slot[i]->clone();
    }
    return (*this);
}

//Interface methods
void MateriaSource::learnMateria( AMateria* m )
{
    for (int i = 0; i < 4; i++)
    {
        if (_slot[i])
            continue ;
        _slot[i] = m->clone();
        break ;
    }
}

AMateria* MateriaSource::createMateria( const std::string& type )
{
    for (int i = 0; i < 4; i++)
    {
        if (_slot[i] && _slot[i]->getType() == type)
            return (_slot[i]->clone());
    }
    return (NULL);
}