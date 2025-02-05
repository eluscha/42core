#include "Point.hpp"

bool bsp( const Point a, const Point b, const Point c, const Point point );

int main( void )
{
    Point a;
    Point b(1, 0);
    Point c(0, 1);
    Point p1(0, -0.01);
    Point p2(0.01, 0.01);
    std::cout << "Point p1 is in ABC triangle: " << (bsp(a,b,c,p1)? "true" : "false") << std::endl;
    std::cout << "Point p2 is in ABC triangle: " << (bsp(a,b,c,p2)? "true" : "false") << std::endl;
    return (0);
}