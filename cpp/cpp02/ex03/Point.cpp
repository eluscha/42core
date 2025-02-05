#include "Point.hpp"

Point::Point() : _x(0), _y(0) {}

Point::Point( const float newx, const float newy ) : _x(newx), _y(newy) {}

Point::Point( const Point& other ) : _x(other._x), _y(other._y) {}

Point& Point::operator=( const Point& other )
{
    if (this != &other)
        std::cerr << "Assignment not possible for Point objects" << std::endl;
    return (*this);
}

Point::~Point() {}

const Fixed& Point::getX( void )
{
    return (_x);
}

const Fixed& Point::getY( void )
{
    return (_y);
}