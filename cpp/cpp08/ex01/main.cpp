#include "Span.hpp"
#include <cstdlib>
//#include <ctime>
#include <iostream>

/*
int main()
{
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
    return 0;
}
*/



int main() {
    Span sp(5);
    try {
        sp.addNumber(10);
        sp.addNumber(3);
        sp.addNumber(9);
        sp.addNumber(2147483647);
        sp.addNumber(-2147483648);
        //sp.addNumber(-3);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        std::cout << "Biggest difference: " << sp.longestSpan() << std::endl;
        std::cout << "Smallest difference: " << sp.shortestSpan() << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n***Testing addition of a range of numbers to Span numbers***" << std::endl;

    Span sp2(10);
    std::vector<int> moreNumbers;
    srand(time(0));
    
    for (unsigned int i = 0; i < sp2.getN(); ++i) {
        int rnum = rand() % 100 + 1;
        std::cout << rnum << ' ';
        moreNumbers.push_back(rnum);
    }
    std::cout << std::endl;
    
    try {
    sp2.addRange(moreNumbers.begin(), moreNumbers.end());
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        std::cout << "Biggest difference: " << sp2.longestSpan() << std::endl;
        std::cout << "Smallest difference: " << sp2.shortestSpan() << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
