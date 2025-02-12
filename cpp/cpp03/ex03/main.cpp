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
    dt.beRepaired(1);
    std::cout << "dt has " << dt.getEnPts() << " energy points" << std::endl;
    dt.highFivesGuys();
    nn.attack("another robot");
    nn = dt;
    nn.attack("another robot");
    nn.whoAmI();
    DiamondTrap cp = DiamondTrap(dt);
    cp.whoAmI();
    cp.attack("dt");
}