#include "Character.hpp"

//Constructors
Character::Character() : _name("noname")
{
    //std::cout << "Character default constructor is called" << std::endl;
    for (int i = 0; i < 4; i++)
        _slot[i] = NULL;
}

Character::Character( std::string const& name ) : _name(name)
{
    //std::cout << "Character parametrized constructor is called" << std::endl;
    for (int i = 0; i < 4; i++)
        _slot[i] = NULL;
}

Character::Character( const Character& other )
{
    //std::cout << "Character copy constructor is called" << std::endl;
    *this = other;
}

//Destructors
Character::~Character()
{
    //std::cout << "Character destructor is called" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        if (_slot[i])
            delete _slot[i];
    }
}

//Overloaded operators
Character& Character::operator=( const Character& other )
{
    if (this == &other)
        return (*this);
    _name = other._name;
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
std::string const& Character::getName() const
{
    return (this->_name);
}

void Character::equip( AMateria* m )
{
    if (m->checkIfTaken())
    {
        std::cout << "The " << m->getType() << " is taken!" << std::endl;
        return ;
    }
    for (int i = 0; i < 4; i++)
    {
        if (_slot[i])
            continue ;
        _slot[i] = m;
        m->setIsTaken(true);
        std::cout << "The " << m->getType() << " was taken by " << _name << std::endl;
        return ;
    }
    std::cout << "All slots are taken! You can unequip a materia to free space." << std::endl;
}
void Character::unequip( int idx )
{
    if (idx < 0 || idx > 3)
    {
        std::cout << "Note: There are only 4 slots (indexed from 0 to 3)." << std::endl;
        return ;
    }
    std::cout << "The " << _slot[idx]->getType() << " was enequiped by " << _name << std::endl;
    _slot[idx]->setIsTaken(false);
    _slot[idx] = NULL;
}

void Character::use( int idx, ICharacter& target )
{
    if (idx < 0 || idx > 3)
    {
        std::cout << "Note: There are only 4 slots (indexed from 0 to 3)." << std::endl;
        return ;
    }
    if (!_slot[idx])
    {
        std::cout << "Slot " << idx << " cannot be used by " << _name << ", as it is empty." << std::endl;
        return ;
    }
    _slot[idx]->use(target);
    delete _slot[idx];
    _slot[idx] = NULL;
}
