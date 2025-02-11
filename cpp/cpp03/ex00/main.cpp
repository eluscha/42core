#include "ClapTrap.hpp"

int main()
{
    ClapTrap c("clap1");
    ClapTrap nn;
    ClapTrap b = ClapTrap(c);
    c.attack("someone");
    b.attack("same poor creature");
    nn.attack("the other robot");
    c.takeDamage(7);
    c.beRepaired(10);
    c.attack("a robot");
    c.takeDamage(15);
    c.beRepaired(2);
    c.attack("cp");
}