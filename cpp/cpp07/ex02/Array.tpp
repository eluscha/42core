#pragma once

#include "Array.hpp"

//Constructors
template <typename T>
Array<T>::Array() : _data(NULL), _size(0) {
    std::cout << "Array default constructor is called" << std::endl;
}

template <typename T>
Array<T>::Array( unsigned int n ) : _size(n) {
    std::cout << "Array parametrized constructor is called" << std::endl;
    _data = new T[n]();
}

template <typename T>
Array<T>::Array( const Array<T>& other ) : _size(other._size) {
    std::cout << "Array copy constructor is called" << std::endl;
    _data = new T[_size]();
    for (std::size_t i = 0; i < _size; ++i)
        _data[i] = other._data[i];
}

//Destructor
template <typename T>
Array<T>::~Array() {
    delete[] _data;
}

//Operator =
template <typename T>
T& Array<T>::operator=( const Array<T>& other ) {
    if (this == &other)
        return (*this);
    delete[] _data;
    _size = other._size;
    _data = new T[_size]();
    for (std::size_t i = 0; i < _size; ++i)
        _data[i] = other._data[i];
    return (*this);
}

//Operator [] (Non-const)
template <typename T>
T& Array<T>::operator[]( int index ) {
    if (index < 0 || (unsigned int)index >= _size) {
        throw std::out_of_range("Index out of bounds"); //inherits from std::exception
    }
    return _data[index];
}

//Size getter
template <typename T>
unsigned int Array<T>::size() const {
    return _size;
}