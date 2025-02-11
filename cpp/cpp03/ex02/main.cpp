#include "FragTrap.hpp"

int main()
{
    FragTrap nn;
    FragTrap fr("John");
    FragTrap fr2 = FragTrap(fr);
    nn.attack("John");
    fr.attack("someone");
    fr.highFivesGuys();
    fr2.attack("a random robot");
}