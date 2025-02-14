#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    const Animal* meta = new Animal();
    const Animal* d = new Dog();
    const Animal* c = new Cat();
    Animal* copy = new Animal(Dog());
    Cat stack_cat1;
    Cat stack_cat2(stack_cat1);

    ((Dog *)d)->getBrain()->setIdea("my first idea!", 0);
    std::cout << "Dog d has an idea: " << ((Dog *)d)->getBrain()->getIdea(0) << std::endl;

    delete meta;
    delete d;
    delete c;
    delete copy;
}