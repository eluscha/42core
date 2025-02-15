#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    const Animal* d = new Dog();
    
    ((Dog *)d)->getBrain()->setIdea("my first idea!", 0);
    std::cout << "Dog d has an idea: " << ((Dog *)d)->getBrain()->getIdea(0) << std::endl;
    Animal* dcopy = new Dog(*(Dog *)d);
    std::cout << "Dog dcopy has an idea: " << ((Dog *)dcopy)->getBrain()->getIdea(0) << std::endl;

    delete d;
    delete dcopy;

    Animal *array[100];
    for (int i = 0; i < 50; i++)
        array[i] = new Dog();
    for (int i = 50; i < 100; i++)
        array[i] = new Cat();

    ((Cat *)array[51])->getBrain()->setIdea("a nice idea here", 10);
    std::cout << "Animal 51 (cat) idea number 10: " << ((Cat *)array[51])->getBrain()->getIdea(10) << std::endl;
    std::cout << "Animal 51 (cat) idea number 9: " << ((Cat *)array[51])->getBrain()->getIdea(9) << std::endl;

    for (int i = 0; i < 100; i++)
        delete array[i];
}