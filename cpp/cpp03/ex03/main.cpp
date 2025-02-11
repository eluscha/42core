#include "DiamondTrap.hpp"

int main()
{
    DiamondTrap nn;
    DiamondTrap dt("John");
    nn.attack("another robot");
    dt.attack("someone");
    dt.whoAmI();
    nn.whoAmI();
    nn.guardGate();
    dt.highFivesGuys();
}