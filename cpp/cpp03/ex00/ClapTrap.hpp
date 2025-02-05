#include <iostream>

class ClapTrap
{
    std::string     _name;
    unsigned int    _hit_pts;
    unsigned int    _en_pts;
    unsigned int    _attack_dmg;

public:

    ClapTrap();
    ClapTrap( const ClapTrap& other );
    ClapTrap& operator=( const ClapTrap& other );
    ClapTrap( std::string name );

    void attack( const std::string& target );
    void takeDamage( unsigned int amount );
    void beRepaired( unsigned int amount );
};