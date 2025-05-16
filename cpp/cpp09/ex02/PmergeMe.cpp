#include "PmergeMe.hpp"

int PmergeMe::compare( int val, int ref ) {
    _numCompar++;
    //std::cout << "comparing " << val << " to " << ref << std::endl;
    if (val == ref)
        return (0);
    else if (val > ref)
        return (1);
    else   
        return (-1);
}

// Orthdox Canoncial Form
PmergeMe::PmergeMe( void ) : _chainSize(0), _numCompar(0) {
    size_t val = 2;
    size_t poweroftwo = 2;
    for (int i = 0; i < JACOBSTHAL_NUMBERS_AMOUNT; ++i) {
        _jacobsthalValues[i] = val;
        poweroftwo *= 2;
        val = poweroftwo - val;
    }
}

PmergeMe::PmergeMe( const PmergeMe& other ) : _chainSize(0), _numCompar(0) {
    (void)other;
}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=( const PmergeMe& other ) {
    (void)other;
    return (*this);
}
