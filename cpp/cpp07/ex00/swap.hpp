#pragma once

template <typename T>
void swap(T& parameter1, T& parameter2) {
    T temp = parameter1;
    parameter1 = parameter2;
    parameter2 = temp;
}