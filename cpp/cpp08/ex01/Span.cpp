#include "Span.hpp"

// Private Constructors
Span::Span( void ) : _N(0), _sorted(true) {}

// Public Constructors
Span::Span( unsigned int N ) : _N(N), _sorted(true) {}
Span::Span( const Span& other ) : _N(other.getN()), _data(other._data), _sorted(other._sorted) {}

// Destructor
Span::~Span( void ) {}

// Overloaded operators
Span& Span::operator=( const Span& other ) {
    if (this == &other)
        return (*this);
    _N = other.getN();
    _data = other._data;
    _sorted = other._sorted;
    return (*this);
}

// N getter
unsigned int Span::getN( void ) const {
    return (_N);
}

// Methods
void Span::addNumber( int num ) {
    if (_data.size() == _N)
        throw std::overflow_error("Exceeded max size");
    
    _data.push_back(num);
    _sorted = false;
}

unsigned int Span::shortestSpan( void ) {
    if (_data.size() < 2)
        throw std::runtime_error("Not enough elements");

    if (!_sorted){
        std::sort(_data.begin(), _data.end());
        _sorted = true;
    }

    unsigned int minDiff = std::numeric_limits<unsigned int>::max();
    unsigned int diff;

    std::vector<int>::iterator it = _data.begin();
    std::vector<int>::iterator next = _data.begin();

    while (++next !=_data.end()) {
        diff = (long long)*next - (long long)*it;
        minDiff = std::min(minDiff, diff);
        ++it;
    }

    return minDiff;
}

unsigned int Span::longestSpan( void ) {
    if (_data.size() < 2)
        throw std::runtime_error("Not enough elements");

    if (!_sorted){
        std::sort(_data.begin(), _data.end());
        _sorted = true;
    }

    return ((long long)*_data.rbegin() - (long long)*_data.begin());
}