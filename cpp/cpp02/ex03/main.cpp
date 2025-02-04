
#include "Fixed.hpp"

/*
int main( void ) 
{
    Fixed a(100);
    Fixed b(-0.125f);
    Fixed const c(--a/b);
    std::cout << "c was made" << std::endl;
    Fixed const d( 100/-0.125f );
    if (c == a / b)
        std::cout << "Equal!" << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "min(a, b) = " << Fixed::min(a,b) << std::endl;
}
*/

int main( void )
{
    Fixed a;
    Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << Fixed::max( a, b ) << std::endl;
    return 0;
}