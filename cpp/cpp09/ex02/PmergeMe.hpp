#pragma once

#include <iostream>
#include <list>

class PmergeMe {
private:
    std::list<int> _chain;

    //Private methods
    template <typename RACont>
    void mergeInsertion( RACont& Cont, RACont& resCont, std::size_t step = 1);

public:
    // Orthdox Canoncial Form
    PmergeMe( void );
    PmergeMe( const PmergeMe& other );
    ~PmergeMe();
    PmergeMe& operator=( const PmergeMe& other );

    // Public Methods
    std::list<int>& getChain( void );

    template <typename RACont>
    RACont getSort( RACont& Cont );

};

template <typename RACont>
RACont PmergeMe::getSort( RACont& Cont ) {
    RACont result;
    mergeInsertion( Cont, result );
    return (result);
}

template <typename RACont>
void PmergeMe::mergeInsertion( RACont& Cont, RACont& resCont, std::size_t step ) {
    typedef typename RACont::iterator iterator;
    std::size_t size = Cont.size() / step;

    //base case
    if (size == 1) {
        for (iterator it = Cont.begin(); it != Cont.end(); ++it)
            std::cout << *it << " ";
        std::cout << std::endl;
        return ;
    }

    bool hasOddElem = size % 2 == 1;

    //split into pairs (bigger, smaller)
    for (iterator it = Cont.begin(); it < Cont.end() - step * (1 + hasOddElem); it += 2 * step) {
        if (*it < *(it + step)) {
            if (step != 1)
                std::swap_ranges(it, it + step, it + step);
            else
                std::iter_swap(it, it + step);

        }
    }

    //recursive call
    mergeInsertion(Cont, resCont, step * 2);

    RACont pend;
    if (!resCont.size())
    {
        resCont.push_back(Cont[step]);
        resCont.push_back(Cont[0]);
    }
    else {   
        for (std::size_t i = 1; i < size - hasOddElem; ++i) {
            if ((i * step) % (step * 2) == 0)
                continue;
            if (i % 2 == 0)
                resCont.push_back(Cont[i * step]);
            else
                pend.push_back(Cont[i * step]);
        }
    }
    if (hasOddElem)
        pend.push_back(*(Cont.end() - step));

    std::cout << "Main chain is: ";
    for (iterator it = resCont.begin(); it != resCont.end(); ++it)
        std::cout << *it << " ";

    std::cout << "\nPending elments: ";
    for (iterator it = pend.begin(); it != pend.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    
    for (iterator itp = pend.begin(); itp != pend.end(); ++itp) {
        std::cout << "inserting " << *itp <<std::endl;
        bool found = false;
        for (iterator itc = resCont.begin(); itc != resCont.end(); ++itc) {
            itc = resCont.begin()
            if (*itp < *itc ) {
                resCont.insert(itc, *itp); //for deque though push_front is possible..
                found = true;
                break ;
            }
        }
        if (!found)
            resCont.push_back(*itp);
    }
    
}
