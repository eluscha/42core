
#include "Zombie.hpp"

int main( void ) 
{
    Zombie* zombie = newZombie("Mortimer");
    zombie->announce();
    delete zombie;

    randomChump("Edgar");

    return (0);
}