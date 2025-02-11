#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap("noname_clap_name")
{
    std::cout << "DiamondTrap default constructor is called" << std::endl;
    _name = "noname";
}

DiamondTrap::DiamondTrap( std::string name ) : ClapTrap(name + "_clap_name")
{
    std::cout << "DiamondTrap name constructor is called" << std::endl;
    _name = name;
}

DiamondTrap::DiamondTrap( const DiamondTrap& other )
{
    std::cout << "DiamondTrap copy constructor is called" << std::endl;
    *this = other;
}

DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap destructor is called" << std::endl;
}

DiamondTrap& DiamondTrap::operator=( const DiamondTrap& other )
{
    if (this == &other)
        return (*this);
    _name = other._name;
    _hit_pts = other._hit_pts;
    _en_pts = other._en_pts;
    _attack_dmg = other._attack_dmg;
    _gateKeeper = other._gateKeeper;
    ClapTrap::_name = other.ClapTrap::_name;
    return (*this);
}

void DiamondTrap::whoAmI()
{
    std::cout << "My name is " << _name << " and my ClapTrap name is " << ClapTrap::_name << std::endl;
}

