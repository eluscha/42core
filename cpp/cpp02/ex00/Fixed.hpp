
#pragma once
#include <iostream>

class Fixed 
{
    int _value;
    static const int _numfract;

public:

    Fixed();
    Fixed( const Fixed &a );
    ~Fixed();
    Fixed& operator=( const Fixed &a );

    int getRawBits( void ) const;
    void setRawBits( int const raw );
    
};
