
#include "Fixed.hpp"

int main( void ) 
{
    Fixed a = Fixed(42);
    Fixed b = Fixed(42.0f);
    if (a == b)
        std::cout << "Equal!" << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
}
