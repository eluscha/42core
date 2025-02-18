#include "Character.hpp"

//Constructors
Character::Character() : _name("noname")
{
    std::cout << "Character default constructor is called" << std::endl;
    for (int i = 0; i < 4; i++)
        _slot[i] = nullptr;
}

Character::Character( std::string const& name ) : _name(name)
{
    std::cout << "Character parametrized constructor is called" << std::endl;
    for (int i = 0; i < 4; i++)
        _slot[i] = nullptr;
}

Character::Character( const Character& other )
{
    std::cout << "Character copy constructor is called" << std::endl;
    *this = other;
}

//Destructors
Character::~Character()
{
    std::cout << "Character destructor is called" << std::endl;
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
    for (int i = 0; i < 4; i++)
    {
        if (_slot[i])
            continue ;
        _slot[i] = m;
        break ;
    }
}
void Character::unequip( int idx )
{
    _slot[idx] = nullptr;
}

void Character::use( int idx, ICharacter& target )
{
    if (idx < 0 || idx > 3)
        return ;
    if (!_slot[idx])
        return ;
    _slot[idx]->use(target);
    delete _slot[idx];
    _slot[idx] = nullptr;
}
