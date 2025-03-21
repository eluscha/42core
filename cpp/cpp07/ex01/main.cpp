#include "iter.hpp"
#include <iostream>

template <typename T>
void example(T t){
	std::cout << '\n' << t;
}

void printInt(int x) {
    std::cout << x << " ";
    //return 0;
}

void incrInt(int& x) {
    ++x;
}

void printStr(std::string& s) {
    std::cout << s << " | ";
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    std::string arr2[] = {"hi", "hello", "bye"};
    ::iter(arr, 5, printInt);
    std::cout << std::endl;
    ::iter(arr2, 3, printStr);
    std::cout << std::endl;

    ::iter(arr, 5, incrInt);
    ::iter(arr, 5, printInt);
    std::cout << std::endl;

    ::iter(arr, 5, example<int>);
    std::cout << std::endl;

    return 0;
}