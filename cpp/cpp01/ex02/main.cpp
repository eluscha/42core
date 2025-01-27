
#include <iostream>

int main( void ) 
{
    std::string mystr = "HI THIS IS BRAIN";
    std::string* stringPTR = &mystr;
    std::string& stringREF = mystr;

    std::cout << "The memory address of mystr: " << &mystr <<std::endl;
    std::cout << "The memory address held by stringPTR: " << stringPTR <<std::endl;
    std::cout << "The memory address held by stringREF: " << &stringREF <<std::endl;

    std::cout << "The value of mystr: " << mystr <<std::endl;
    std::cout << "The value pointed to by sstringPTR: " << *stringPTR <<std::endl;
    std::cout << "The value pointed to by stringREF: " << stringREF <<std::endl;
}