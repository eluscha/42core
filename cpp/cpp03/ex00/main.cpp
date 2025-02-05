#include "ClapTrap.hpp"

int main()
{
    ClapTrap c("clap1");
    ClapTrap t("clap2");
    c.attack("someone");
    t.takeDamage(6);
    t.takeDamage(4);
    t.takeDamage(2);
}