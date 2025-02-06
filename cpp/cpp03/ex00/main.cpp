#include "ClapTrap.hpp"

int main()
{
    ClapTrap c("clap1");
    c.attack("someone");
    c.takeDamage(7);
    c.beRepaired(10);
    c.attack("a robot");
    c.takeDamage(15);
    c.beRepaired(2);
    c.attack("cp");
}