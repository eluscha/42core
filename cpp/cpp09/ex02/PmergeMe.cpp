#include "PmergeMe.hpp"

// Orthdox Canoncial Form
PmergeMe::PmergeMe( void ) {}

PmergeMe::PmergeMe( const PmergeMe& other ) 
    :  _chain(other._chain) {}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=( const PmergeMe& other ) {
    if (this != &other)
        _chain = other._chain;
    return (*this);
}

std::list<int>& PmergeMe::getChain( void ) {
    return (_chain);
}

