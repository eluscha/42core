#pragma once

#include <iostream>
#include <stdexcept>

template <typename T>
class Array {
private:
    T*           _data; 
    unsigned int _size;

public:
    //Constructors
    Array();
    Array( unsigned int n );
    Array( const Array<T>& other );

    //Destructor
    ~Array();

    //Overloaded operators
    T& operator=( const Array<T>& other );
    T& operator[]( int index );
    //const T& operator[](std::size_t index) const;

    //size getter
    unsigned int size() const;
};

#include "Array.tpp"