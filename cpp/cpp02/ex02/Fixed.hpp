
#pragma once
#include <iostream>
#include <cmath>

class Fixed 
{
    int _value;
    static const int _numfract;

public:

    Fixed();
    Fixed( const int ival );
    Fixed( const float fval);
    Fixed( const Fixed &other );
    ~Fixed();
    Fixed& operator=( const Fixed &other );

    bool operator==(const Fixed &f) const
    {
        return (_value == f._value);
    }

    bool operator!=(const Fixed &f) const
    {
        return (_value != f._value);
    }

    bool operator>=(const Fixed &f) const
    {
        return (_value >= f._value);
    }

    bool operator<=(const Fixed &f) const
    {
        return (_value <= f._value);
    }

    bool operator>(const Fixed &f) const
    {
        return (_value > f._value);
    }

    bool operator<(const Fixed &f) const
    {
        return (_value < f._value);
    }

    Fixed operator+(Fixed const& other) 
    {
        return Fixed(this->getRawBits() + other.getRawBits());
    }

    int getRawBits( void ) const;
    void setRawBits( int const raw );
    
    float toFloat( void ) const;
    int toInt( void ) const;
    
};

std::ostream& operator<<(std::ostream &o, Fixed const &fixed);


