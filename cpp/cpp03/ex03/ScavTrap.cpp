#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap(), _gateKeeper(false)
{
    std::cout << "ScavTrap default constructor is called" << std::endl;
	_hit_pts = 100;
	_en_pts = 50;
	_attack_dmg = 20;
}

ScavTrap::ScavTrap( std::string name ) : ClapTrap(name), _gateKeeper(false)
{
    std::cout << "ScavTrap name constructor is called" << std::endl;
	_hit_pts = 100;
	_en_pts = 50;
	_attack_dmg = 20;
}

ScavTrap::ScavTrap( const ScavTrap& other ) : ClapTrap(other), _gateKeeper(other._gateKeeper)
{
    std::cout << "ScavTrap copy constructor is called" << std::endl;
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap destructor is called" << std::endl;
}

ScavTrap& ScavTrap::operator=( const ScavTrap& other )
{
    if (this == &other)
        return (*this);
    _name = other._name;
    _hit_pts = other._hit_pts;
    _en_pts = other._en_pts;
    _attack_dmg = other._attack_dmg;
	_gateKeeper = other._gateKeeper;
    return (*this);
}

void ScavTrap::attack( const std::string& target )
{
    if (!_en_pts)
    {
        std::cout << "ScavTrap " << _name << " cannot attack" << std::endl;
        return ;
    }
    --_en_pts;
    std::cout << "ScavTrap " << _name << " attacks " << target << ", causing ";
    std::cout << _attack_dmg << " points of damage!" << std::endl;
}

void ScavTrap::guardGate( void )
{
    _gateKeeper = true;
    std::cout << "ScavTrap " << _name << " is now a gate keeper." << std::endl;
}
