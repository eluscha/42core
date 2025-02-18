#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"

int main()
{
    AMateria* ice1 = new Ice();
    //AMateria* meta = new AMateria("ice");

    Character player;
    player.equip(ice1);

}