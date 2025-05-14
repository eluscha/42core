#include "PmergeMe.hpp"

#include <vector>
#include <deque>

#include <sstream>
#include <string>

#include <cstdlib>

int get_num(char *str) {
    if (!str || *str == '\0') {
        std::cerr << "Error: NULL or empty string in argv" << std::endl;
        return (0);
    }

    char* endptr;
    errno = 0;
    long val = std::strtol(str, &endptr, 10);

    // Check: entire string was consumed, and int is positive and within range
    if (*endptr != '\0' || errno == ERANGE || val < 1 || val > INT_MAX) {
        std::cerr << "Error: not a valid integer: " << str << std::endl; 
        return (0);
    }

    return(static_cast<int>(val));
}

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cerr << "Usage: ./PmergeMe {1 or more positive numbers to sort}" << std::endl;
        return (1);
    }

    std::vector<int> vec;
    std::deque<int> deq;
    int num;

    for (int i = 1; i < argc; ++i) {
        num = get_num(argv[i]);
        if (!num)
            return (1);
        vec.push_back(num);
        deq.push_back(num);
    }


    // Print to confirm
    // std::cout << "Parsed values: ";
    // for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;


    PmergeMe PM;

    std::clock_t start = std::clock();

    vec = PM.getSort(vec); 

    std::clock_t end = std::clock();

    double elapsed_us = 1e6 * (end - start) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : "
              << std::fixed << std::setprecision(5) << elapsed_us
              << " us" << std::endl;

    std::cout << "Result: ";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    std::cout << "\n\nNow for deque \n" << std::endl;

    PmergeMe PM2;

    start = std::clock();
    deq = PM2.getSort(deq);
    end = std::clock();

    elapsed_us = 1e6 * (end - start) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::deque : "
              << std::fixed << std::setprecision(5) << elapsed_us
              << " us" << std::endl;

    std::cout << "Result: ";

    for (size_t i = 0; i < deq.size(); ++i)
        std::cout << deq[i] << " ";
    std::cout << std::endl;

    return 0;
}