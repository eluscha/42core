#include "AAnimal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    Dog d;
    Cat c;
    AAnimal* dog = new Dog();
    //AAnimal* meta = new AAnimal();

    c.getBrain()->setIdea("my first cat idea!", 0);
    std::cout << "Cat c has an idea: " << c.getBrain()->getIdea(0) << std::endl;

    AAnimal* copy = new Cat(c);
    std::cout << "Cat copy has an idea: " << ((Cat *)copy)->getBrain()->getIdea(0) << std::endl;

    delete dog;
    delete copy;
}