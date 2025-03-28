#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>

int main() {
    const int arr[] = {1, 2, 4, 5, 3, 10, 3, 20, 30, 40, 30, 3, 100};
    std::vector<int> vec(arr, arr + sizeof(arr) / sizeof(int));
    std::list<int> lst(arr, arr + sizeof(arr) / sizeof(int));

    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }

    int value = 3;

    try {
        std::cout << "Searching for " << value << " in vec" << std::endl;
        std::cout << std::distance(vec.begin(), easyfind(vec, value)) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        std::cout << "Searching for " << value << " in lst" << std::endl;
        std::cout << std::distance(lst.begin(), easyfind(lst, value)) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}