#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap("noname_clap_name")
{
    std::cout << "DiamondTrap constructor is called" << std::endl;
    _name = "noname";
    _hit_pts = FragTrap::_hit_pts;
    _en_pts = ScavTrap::_en_pts;
    _attack_dmg = FragTrap::_attack_dmg;
}

DiamondTrap::DiamondTrap( std::string name ) : ClapTrap(name + "_clap_name")
{
    std::cout << "DiamondTrap name constructor is called" << std::endl;
    _name = name;
    _hit_pts = FragTrap::_hit_pts;
    _en_pts = ScavTrap::_en_pts;
    _attack_dmg = FragTrap::_attack_dmg;
}

DiamondTrap::DiamondTrap( const DiamondTrap& other )
{
    std::cout << "DiamondTrap copy constructor is called" << std::endl;
    *this = other;
}

void DiamondTrap::attack( const std::string& target )
{
    ScavTrap::attack(target);
}

