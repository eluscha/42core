
#include "Fixed.hpp"

const int Fixed::_numfract = 8;

Fixed::Fixed() : _value(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed( const int ival ) : _value(ival << _numfract)
{
    std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed( const float fval )
{
    std::cout << "Float constructor called" << std::endl;
    int fp_one = 1 << _numfract;
    _value = roundf(fval * fp_one);
}

Fixed::Fixed (const Fixed& other)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& other) 
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) 
        _value = other.getRawBits();;
    return *this;
}

int Fixed::getRawBits( void ) const
{
    return (_value);
}

void Fixed::setRawBits( int const raw )
{
    _value = raw;
}

float Fixed::toFloat( void ) const
{
    int fp_one = 1 << _numfract;
    return ((float)_value / fp_one);
}

int Fixed::toInt( void ) const
{
    return (getRawBits() >> _numfract);
}

std::ostream& operator<<(std::ostream &o, Fixed const &fixed)
{
    o << fixed.toFloat();
    return (o);
}