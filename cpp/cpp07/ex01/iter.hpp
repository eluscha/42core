#pragma once

#include <cstddef>

/*
//less flexible option, as func has to match void (*func)(T&)

template <typename T>
void iter(T* arr, std::size_t len, void (*func)(T&)) {
    for (std::size_t i = 0; i < len; ++i) {
        func(arr[i]); 
    }
}
*/


template <typename T, typename Func>
void iter(T* arr, std::size_t len, Func func) {
    for (std::size_t i = 0; i < len; ++i) {
        func(arr[i]); 
    }
}
