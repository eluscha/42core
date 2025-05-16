#include "PmergeMe.hpp"

#include <vector>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <cerrno>
#include <limits.h>

//./PmergeMe $(shuf -i 1-1000 -n 10 | tr '\n' ' ') //to test

static int get_num(char *str) {
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

static bool vec_equal_deq(std::vector<int>& vec, std::deque<int>& deq, bool check_sorted) {
    if (vec.size() != deq.size())
        return (false);
    
    std::deque<int>::iterator itd = deq.begin();
    std::vector<int>::iterator itv2 = vec.begin();

    for (std::vector<int>::iterator itv = vec.begin(); itv != vec.end(); ++itv) {
        if (*itv != *itd)
            return (false);
        ++itd;
        //check for sort;
        if (check_sorted) {
            ++itv2;
            if (itv2 != vec.end() && *itv2 < *itv)
                std::cout << "Error: not sorted: " << *itv2 << " < " << *itv << std::endl;
        }
    }
    return (true);
}

static void print_vec(std::vector<int>& vec, bool print_all) {
    size_t print_amount = 30;
    size_t limit = vec.size();
    if (!print_all && vec.size() > print_amount)
        limit = print_amount;
    for (size_t i = 0; i < limit; ++i)
        std::cout << vec[i] << " ";
    if (!print_all && vec.size() > print_amount)
        std::cout << "...";
    std::cout << std::endl;
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

    if (!vec_equal_deq(vec, deq, false)) { //compare vector and deque without checking for them being sorted
        std::cerr << "Error: vector and deque content not equal" << std::endl;
        return (1);
    }

    std::cout << "Before: ";
    print_vec(vec, false);

    PmergeMe PM;
    std::clock_t start = std::clock();
    vec = PM.getSort(vec); 
    std::clock_t end = std::clock();
    double elapsed_us_vec = 1e6 * (end - start) / CLOCKS_PER_SEC;

    PmergeMe PM2;

    start = std::clock();
    deq = PM2.getSort(deq);
    end = std::clock();
    double elapsed_us_deq = 1e6 * (end - start) / CLOCKS_PER_SEC;

    if (!vec_equal_deq(vec, deq, true)) { //compare vector and deque AND check for them being sorted
        std::cerr << "Error: vector and deque content not equal" << std::endl;
        return (1);
    }

    std::cout << "After: ";
    print_vec(vec, false);

    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : "
              << std::fixed << std::setprecision(5) << elapsed_us_vec
              << " us" << std::endl;

    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::deque : "
              << std::fixed << std::setprecision(5) << elapsed_us_deq
              << " us" << std::endl;

    return 0;
}