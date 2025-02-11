#include "ScavTrap.hpp"

int main()
{
    ScavTrap s1("s1");
    s1.attack("someone");
    s1.guardGate();
    ScavTrap s2;
    ScavTrap s3 = ScavTrap(s2);
    s2.attack("a robot");
    s3.attack("s2");
}