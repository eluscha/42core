#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>
#include <exception>

void identify( Base* p )
{
    if (dynamic_cast<A*>(p) != NULL) //Downcasting p to A*
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p) != NULL) //Downcasting p to B*
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p) != NULL) //Downcasting p to C*
        std::cout << "C" << std::endl;
}

void identify( Base& p )
{
    try 
    {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return ;
    } 
    catch (const std::exception& e) {} // Catches all standard exceptions
    try 
    {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return ;
    } 
    catch (...) {}
    try 
    {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return ;
    } 
    catch (...) {}
}

