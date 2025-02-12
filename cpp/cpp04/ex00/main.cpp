#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    const Animal* meta = new Animal();
    const Animal* d = new Dog();
    const Animal* c = new Cat();
    std::cout << "d type is " << d->getType() << " " << std::endl;
    std::cout << "c type is " << c->getType() << " " << std::endl;
    std::cout << "The dog says ";
    d->makeSound(); //will output the dog sound!
    std::cout << "The cat says ";
    c->makeSound(); //will output the cat sound!
    std::cout << "The animal says ";
    meta->makeSound();
}