#include "Point.hpp"

Fixed crossProduct(Point A, Point B, Point P)
{
    return (B.getX()-A.getX()) * (P.getY()-A.getY()) - (B.getY()-A.getY()) * (P.getX()-A.getX());
}

bool bsp( const Point a, const Point b, const Point c, const Point point )
{
    Fixed cross1 = crossProduct(a, b, point);
    Fixed cross2 = crossProduct(b, c, point);
    Fixed cross3 = crossProduct(c, a, point);

    return (cross1 > 0 && cross2 > 0 && cross3 > 0) || 
           (cross1 < 0 && cross2 < 0 && cross3 < 0);
} 