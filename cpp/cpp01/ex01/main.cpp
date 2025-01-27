
#include "Zombie.hpp"

int main( void ) 
{
    int N = 2;

    Zombie* horde = zombieHorde(N, "Mortimer");

    if (!horde)
        return (1);

    for (int i = 0; i < N; i++)
        horde[i].announce();
    
    delete[] horde;
    return (0);
}