#include "PmergeMe.hpp"

//Jakoc
const std::size_t PmergeMe::_jacobsthalValues[] = {
    2u, 2u, 6u, 10u, 22u, 42u, 106u, 190u,
    402u, 782u, 1586u, 3150u, 6346u, 12646u,
    25438u, 50630u, 101702u, 202962u, 407366u,
    813290u, 1624014u, 3240598u, 6484626u,
    12964850u, 25994102u, 51953754u,
    103987558u, 208976066u, 419951182u,
    839903314u, 1679937678u, 3359854306u
};

int PmergeMe::compare( int val, int ref ) {
    _numCompar++;
    if (val == ref)
        return (0);
    else if (val > ref)
        return (1);
    else   
        return (-1);
}

// Orthdox Canoncial Form
PmergeMe::PmergeMe( void ) : _chainSize(0), _numCompar(0) {}

PmergeMe::PmergeMe( const PmergeMe& other ) : _chainSize(0), _numCompar(0) {
    (void)other;
}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=( const PmergeMe& other ) {
    (void)other;
    return (*this);
}


