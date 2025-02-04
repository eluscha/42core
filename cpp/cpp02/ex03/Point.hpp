#pragma once

#include "Fixed.hpp"

class Point
{
    Fixed const x;
    Fixed const y;

public:
    Point();
    Point( float const newx, float const newy );
    Point( Point const& p );
    Point& operator=( Point const& p);
};