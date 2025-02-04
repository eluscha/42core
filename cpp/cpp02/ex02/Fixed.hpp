
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

    int getRawBits( void ) const;
    void setRawBits( int const raw );
    
    float toFloat( void ) const;
    int toInt( void ) const;

    bool operator==(const Fixed &f) const;
    bool operator!=(const Fixed &f) const;
    bool operator>=(const Fixed &f) const;
    bool operator<=(const Fixed &f) const;
    bool operator>(const Fixed &f) const;
    bool operator<(const Fixed &f) const;

    Fixed operator+(Fixed const& other) const;
    Fixed operator-(Fixed const& other) const;
    Fixed operator*(Fixed const& right) const;
    Fixed operator/(Fixed const& div) const;

    Fixed& operator++();
    Fixed operator++(int);
    Fixed& operator--();
    Fixed operator--(int);

    static Fixed& min(Fixed& first, Fixed& second);
    static Fixed const& min(Fixed const& first, Fixed const& second);
    static Fixed& max(Fixed& first, Fixed& second);
    static Fixed const& max(Fixed const& first, Fixed const& second);
};

std::ostream& operator<<(std::ostream &o, Fixed const &fixed);


