#pragma once

#include "easyfind.hpp"

template <typename T>
typename T::iterator easyfind(T& cont, int val)
{
    typename T::iterator iter;

    //std::find from <algorithm> can be used to locate the first occurrence of val in any sequence container 
    iter = std::find(cont.begin(), cont.end(), val); 

    if (iter == cont.end())
        throw std::out_of_range("Value not found in container");
    
    return (iter);
}