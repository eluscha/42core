#include "PmergeMe.hpp"

#include <vector>
#include <deque>

int main(int argc, char **argv){
    if (argc != 2) {
        std::cerr << "Usage: ..." << std::endl;
        return (1);
    }
    std::string input = argv[1];
    std::vector<int> vec;

    for (int i = 0; i < 10; ++i)
        vec.push_back(i);
    
    PmergeMe PM;
    vec = PM.getSort(vec); 


    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    return 0;
}