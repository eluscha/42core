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
    nn.attack("another robot");
    nn = dt;
    nn.attack("another robot");
    nn.whoAmI();
}