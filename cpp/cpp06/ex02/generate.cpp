#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>
#include <iostream>

Base* generate( void )
{
    srand(time(0));
    int rand_choice = rand() % 3;
    switch (rand_choice)
    {
        case 0:
            return (new A);
        case 1:
            return (new B);
        case 2:
            return (new C);
        default:
            std::cerr << "Error in rand num generation" << std::endl;
            return (NULL);
    }

}