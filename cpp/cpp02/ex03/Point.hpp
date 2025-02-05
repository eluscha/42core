#pragma once

#include "Fixed.hpp"

class Point
{
    const Fixed _x;
    const Fixed _y;

public:
    Point();
    Point( const float newx, const float newy );
    Point( const Point& other );
    Point& operator=( const Point& other );
    ~Point();

    const Fixed& getX( void );
    const Fixed& getY( void );
};