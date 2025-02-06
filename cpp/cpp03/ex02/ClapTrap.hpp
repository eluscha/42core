#pragma once
#include <iostream>

class ClapTrap
{
    
protected:

    std::string     _name;
    unsigned int    _hit_pts;
    unsigned int    _en_pts;
    unsigned int    _attack_dmg;

public:

    ClapTrap();
    ClapTrap( std::string name );
    ClapTrap( const ClapTrap& other );
    ClapTrap& operator=( const ClapTrap& other );
    ~ClapTrap();

    void attack( const std::string& target );
    void takeDamage( unsigned int amount );
    void beRepaired( unsigned int amount );
};