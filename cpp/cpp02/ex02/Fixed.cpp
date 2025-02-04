
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

bool Fixed::operator==(const Fixed &f) const
{
    return (_value == f._value);
}

bool Fixed::operator!=(const Fixed &f) const
{
    return (_value != f._value);
}

bool Fixed::operator>=(const Fixed &f) const
{
    return (_value >= f._value);
}

bool Fixed::operator<=(const Fixed &f) const
{
    return (_value <= f._value);
}

bool Fixed::operator>(const Fixed &f) const
{
    return (_value > f._value);
}

bool Fixed::operator<(const Fixed &f) const
{
    return (_value < f._value);
}

Fixed Fixed::operator+(Fixed const& right) const
{
    Fixed res;
    res.setRawBits(_value + right._value);
    return res; 
}

Fixed Fixed::operator-(Fixed const& right) const
{
    Fixed res;
    res.setRawBits(_value - right._value);
    return res; 
}

Fixed Fixed::operator*(Fixed const& right) const
{
    Fixed res;
    res.setRawBits(((long)_value * right._value) >> _numfract);
    return res; 
}

Fixed Fixed::operator/(Fixed const& div) const
{
    if (div._value == 0)
        throw std::runtime_error("Division by zero");
    
    Fixed res;
    res.setRawBits(((long)_value << _numfract) / div._value);
    return res; 
}

Fixed& Fixed::operator++()
{
    _value++;// actual increment takes place here
    return *this; // return new value by reference
}
 
Fixed Fixed::operator++(int)
{
    Fixed old = *this; // copy old value
    operator++();  // prefix increment
    return old;    // return old value
}
 
Fixed& Fixed::operator--()
{
    _value--;// actual decrement takes place here
    return *this; // return new value by reference
}
 
Fixed Fixed::operator--(int)
{
    Fixed old = *this;
    operator--();
    return old;
}

Fixed& Fixed::min(Fixed& first, Fixed& second)
{
    if (first <= second)
        return (first);
    return (second);
}

Fixed const& Fixed::min(Fixed const& first, Fixed const& second)
{
    if (first <= second)
        return (first);
    return (second);
}

Fixed& Fixed::max(Fixed& first, Fixed& second)
{
    if (first >= second)
        return (first);
    return (second);
}

Fixed const& Fixed::max(Fixed const& first, Fixed const& second)
{
    if (first >= second)
        return (first);
    return (second);
}

std::ostream& operator<<(std::ostream &o, Fixed const &fixed)
{
    o << fixed.toFloat();
    return (o);
}