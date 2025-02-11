#include "FragTrap.hpp"

FragTrap::FragTrap() 
{
    std::cout << "FragTrap default constructor is called" << std::endl;
	_hit_pts = 100;
	_en_pts = 100;
	_attack_dmg = 30;
}

FragTrap::FragTrap( std::string name ) : ClapTrap(name)
{
    std::cout << "FragTrap name constructor is called" << std::endl;
	_hit_pts = 100;
	_en_pts = 100;
	_attack_dmg = 30;
}

FragTrap::FragTrap( const FragTrap& other ) : ClapTrap(other)
{
    std::cout << "FragTrap copy constructor is called" << std::endl;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap destructor is called" << std::endl;
}

FragTrap& FragTrap::operator=( const FragTrap& other )
{
    if (this == &other)
        return (*this);
    _name = other._name;
    _hit_pts = other._hit_pts;
    _en_pts = other._en_pts;
    _attack_dmg = other._attack_dmg;
    return (*this);
}

void FragTrap::attack( const std::string& target )
{
    if (!_en_pts || !_hit_pts)
    {
        std::cout << "FragTrap " << _name << " cannot attack" << std::endl;
        return ;
    }
    --_en_pts;
    std::cout << "FragTrap " << _name << " attacks " << target << ", causing ";
    std::cout << _attack_dmg << " points of damage!" << std::endl;
}

void FragTrap::highFivesGuys( void )
{
    std::cout << "FragTrap " << _name << " says: High five, guys?" << std::endl;
}