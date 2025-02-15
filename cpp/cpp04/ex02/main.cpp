#include "AAnimal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    Dog d;
    Cat c;
    Animal* dog = new Dog();
    //Animal* meta = new Animal();
    delete dog;
}