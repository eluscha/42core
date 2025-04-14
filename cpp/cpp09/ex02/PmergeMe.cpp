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

// Orthdox Canoncial Form
PmergeMe::PmergeMe( void ) : _chainSize(0) {}

PmergeMe::PmergeMe( const PmergeMe& other ) : _chainSize(other._chainSize) {}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=( const PmergeMe& other ) {
    if (this != &other)
        _chainSize = other._chainSize;
    return (*this);
}

