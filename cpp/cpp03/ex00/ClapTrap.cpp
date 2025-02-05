#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("noname"), _hit_pts(10), _en_pts(10), _attack_dmg(0) {}

ClapTrap::ClapTrap( std::string name ) : _name(name), _hit_pts(10), _en_pts(10), _attack_dmg(0) {}

ClapTrap::ClapTrap( const ClapTrap& other )
{
    *this = other;
}

ClapTrap& ClapTrap::operator=( const ClapTrap& other )
{
    if (this == &other)
        return (*this);
    _name = other._name;
    _hit_pts = other._hit_pts;
    _en_pts = other._en_pts;
    _attack_dmg = other._attack_dmg;
    return (*this);
}

void ClapTrap::attack( const std::string& target )
{
    if (!_en_pts)
    {
        std::cout << _name << " cannot attack" << std::endl;
        return ;
    }
    --_en_pts;
    std::cout << "ClapTrap " << _name << " attacks " << target << ", causing ";
    std::cout << _attack_dmg << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage( unsigned int amount )
{
    if (amount >= _hit_pts)
        _hit_pts = 0;
    else
        _hit_pts -= amount;
    std::cout << "ClapTrap " << _name << " takes damage of " << amount << " points. ";
    std::cout << _name << " now has " << _hit_pts << " hit points left." << std::endl;
}

void ClapTrap::beRepaired( unsigned int amount )
{
    if (!_en_pts)
    {
        std::cout << _name << " cannot be repaired" << std::endl;
        return ;
    }
    --_en_pts;
    _hit_pts += amount;
    std::cout << "ClapTrap " << _name << " is repaired. ";
    std::cout << _name << " now has " << _hit_pts << " hit points." << std::endl;
}