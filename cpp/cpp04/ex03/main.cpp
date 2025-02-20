#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"

int main()
{
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    ICharacter* me = new Character("me");
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    ICharacter* bob = new Character("bob");
    me->use(0, *bob);
    me->use(1, *bob);

    //extra tests
    AMateria* ice1 = new Ice();
    me->equip(ice1); 
    bob->equip(ice1); //is taken already
    me->unequip(0); 
    me->use(0, *bob);
    bob->equip(ice1); //is available. Will not be used

    src->learnMateria(ice1);
    src->learnMateria(ice1);
    AMateria *ice2 = src->createMateria("ice");
    me->equip(ice2);
    me->equip(ice2);

    AMateria *cure1 = new Cure();
    std::cout << "cure1 type is " << cure1->getType() << std::endl;
    *cure1 = *ice2;
    std::cout << "cure1 type is " << cure1->getType() << std::endl;
    me->equip(new Cure());
    me->equip(new Ice());
    me->equip(cure1);
    me->equip(new Cure());
    me->use(5, *bob);

    ICharacter *copy = new Character(*(Character *)me);

    me->unequip(5);
    me->unequip(3);
    me->unequip(2);

    me->use(3, *bob); //cannot use
    copy->use(3, *bob); // can use, as it was a deep copy

    src->learnMateria(cure1); 
    src->learnMateria(ice2);

    delete bob;
    delete me;
    delete copy;
    delete src;

    AMateria::cleanup(); //has to be last, cleans up the "floor"
}