#pragma once

#include <iostream>
#include <list>
#include <vector>


class PmergeMe {
private:
    std::list<std::size_t> _chain;

    //Private methods
    template <typename RACont>
    void mergeInsertion( RACont& Cont, std::size_t step = 1);

    template <typename RACont>
    void insert( RACont& Cont, std::vector<int>& pend  );

public:
    // Orthdox Canoncial Form
    PmergeMe( void );
    PmergeMe( const PmergeMe& other );
    ~PmergeMe();
    PmergeMe& operator=( const PmergeMe& other );

    // Public Methods
    template <typename RACont>
    RACont getSort( RACont& Cont );

};

template <typename RACont>
RACont PmergeMe::getSort( RACont& Cont ) {
    _chain.clear();
    RACont result;
    mergeInsertion(Cont);
    for (std::list<std::size_t>::iterator it = _chain.begin(); it != _chain.end(); ++it)
        result.push_back(Cont[*it]);
    return (result);
}

template <typename RACont>
void PmergeMe::mergeInsertion( RACont& Cont, std::size_t step ) {
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
    mergeInsertion(Cont, step * 2);
    std::vector<int> pend;
    pend.reserve(_chain.size() + hasOddElem); //cannot be bigger than that

    if (!_chain.size())
    {
        _chain.push_back(Cont[step +  step / 2]);
        _chain.push_back(Cont[step]);
        _chain.push_back(Cont[0]);
    }
    else {
        for (std::list<std::size_t>::iterator it = _chain.begin(); it != _chain.end(); ++it)
            pend.push_back(Cont[*it + step]); //get a loser counterpart
    }
    if (hasOddElem)
        pend.push_back(*(Cont.end() - step));

    std::cout << "Main chain is: ";
    for (std::list<std::size_t>::iterator it = _chain.begin(); it != _chain.end(); ++it)
        std::cout << *it << " ";

    std::cout << "\nPending elments: ";
    for (std::vector<int>::iterator it = pend.begin(); it != pend.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    
    
}

template <typename RACont>
void PmergeME::insert( RACont& Cont, std::vector<int>& pend  ) {
    for (std::vector<int>::iterator itp = pend.begin(); itp != pend.end(); ++itp) {
        std::cout << "inserting " << *itp <<std::endl;
        bool found = false;
        for (std::list<size_t>::iterator itc = _chain.begin(); itc != _chain.end(); ++itc) {
            if (*itp < *itc ) {
                _chain.insert(itc, *itp); //for deque though push_front is possible..
                found = true;
                break ;
            }
        }
        if (!found)
            _chain.push_back(*itp);
    }
}