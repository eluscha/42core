#include "swap.hpp"
#include "min.hpp"
#include "max.hpp"
#include <iostream>

int main( void ) 
{
    int a = 2;
    int b = 3;
    ::swap( a, b );
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min(a,b) = " << ::min( a, b ) << std::endl;
    std::cout << "max(a,b) = " << ::max( a, b ) << std::endl;
    std::string c = "chaine1";
    std::string d = "chaine2";
    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min(c,d) = " << ::min( c, d ) << std::endl;
    std::cout << "max(c,d) = " << ::max( c, d ) << std::endl;
    
    /*
    std::string e = max(c,d);
    std::cout << "min(c,e) = " << ::min( c, e ) << std::endl;
    e += "0";
    ::swap<std::string>(c,e);
    std::cout << "c = " << c << ", e = " << e << std::endl;
    std::cout << "max(c,e) = " << ::max( c, e ) << std::endl;
    */

    return 0;
}