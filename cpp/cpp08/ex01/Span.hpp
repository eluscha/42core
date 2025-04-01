#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <stdexcept>

class Span {
private:

    unsigned int        _N;
    std::vector<int>    _data;
    bool                _sorted;

    //Private Constructors
    Span( void );

public:
    //Public Constructors
    Span( unsigned int N );
    Span( const Span& other );

    //Destructor
    ~Span( void );

    //Overloaded operators
    Span& operator=( const Span& other );

    //N getter
    unsigned int getN( void ) const;

    //Methods
    void addNumber( int num );
    unsigned int shortestSpan( void );
    unsigned int longestSpan( void );

    //Templates
    template <typename Iterator>
    void addRange(Iterator begin, Iterator end) {
        for (Iterator it = begin; it != end; ++it) {
            addNumber(*it);
        }
    }
};
