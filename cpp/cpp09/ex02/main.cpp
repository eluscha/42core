#include "PmergeMe.hpp"

#include <vector>
#include <deque>

#include <sstream>
#include <string>

#include <cstdlib>


int main(int argc, char **argv){
    if (argc != 2) {
        std::cerr << "Usage: ..." << std::endl;
        return (1);
    }

    std::string input(argv[1]);
    std::istringstream iss(input);
    std::vector<int> vec;
    std::deque<int> deq;
    int num;

    while (iss >> num) {
        vec.push_back(num);
        deq.push_back(num);
    }


    // Print to confirm
    std::cout << "Parsed values: ";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    PmergeMe PM;
    vec = PM.getSort(vec); 

    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    std::cout << " Now for deque " << std::endl;

    PmergeMe PM2;
    deq = PM2.getSort(deq); 

    for (size_t i = 0; i < deq.size(); ++i)
        std::cout << deq[i] << " ";
    std::cout << std::endl;

    return 0;
}