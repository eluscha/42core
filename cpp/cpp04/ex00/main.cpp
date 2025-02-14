#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    const Animal* meta = new Animal();
    const Animal* d = new Dog();
    const Animal* c = new Cat();
    Animal* copy = new Animal(Dog());
    Cat stack_cat1;
    Cat stack_cat2(stack_cat1);

    std::cout << "meta type is " << meta->getType() << std::endl;
    std::cout << "d type is " << d->getType() << std::endl;
    std::cout << "c type is " << c->getType() << std::endl;
    std::cout << "copy type is " << copy->getType() << std::endl;
    std::cout << "stack_cat1 type is " << stack_cat1.getType() << std::endl;
    std::cout << "stack_cat2 type is " << stack_cat2.getType() << std::endl;

    std::cout << "The dog says ";
    d->makeSound(); //will output the dog sound!
    std::cout << "The cat says ";
    c->makeSound(); //will output the cat sound!
    std::cout << "The animal says ";
    meta->makeSound();
    std::cout << "The copy says ";
    copy->makeSound();
    std::cout << "stack_cats say: ";
    stack_cat1.makeSound();
    stack_cat2.makeSound();

    delete meta;
    delete d;
    delete c;
    delete copy;

    std::cout << "\nNow the wrong animals will be tested" << std::endl;
    WrongCat *wrct1 = new WrongCat();
    std::cout << "wrct1 is a " << wrct1->getType() << "and it says: ";
    wrct1->makeSound();
    WrongAnimal *wrct2 = new WrongCat();
    std::cout << "wrct2 is a " << wrct2->getType() << "and it says: ";
    wrct2->makeSound();

    delete wrct1;
    delete wrct2;
}