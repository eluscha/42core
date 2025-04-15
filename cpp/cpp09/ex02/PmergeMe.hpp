#pragma once

#include <iostream>
#include <list>
#include <vector>

#include <bits/stdc++.h>



class PmergeMe {
private:

    static const std::size_t _jacobsthalValues[];
    std::size_t _chainSize;
    std::size_t _numCompar;
    int compare ( int val, int ref );
    //Private methods tenmplates
    template <typename RACont>
    bool mergeInsertion( RACont& inputCont, RACont& resCont, std::size_t step = 1 );

    template <typename RACont>
    bool insert_group( RACont& Cont, RACont& chain, std::vector<int>& pend, std::size_t prev_end, std::size_t round );

    template <typename RACont>
    std::size_t binary_search( RACont& Cont, RACont& chain, int pend_val, std::size_t start_idx, std::size_t end_idx );


public:
    // Orthdox Canoncial Form
    PmergeMe( void );
    PmergeMe( const PmergeMe& other );
    ~PmergeMe();
    PmergeMe& operator=( const PmergeMe& other );

    // Public Methods templates
    template <typename RACont>
    RACont getSort( RACont Cont );

};

template <typename RACont>
RACont PmergeMe::getSort( RACont copy ) {
    typedef typename RACont::iterator iterator;
    _chainSize = 0;
    _numCompar = 0;

    if (copy.size() < 2)
        return copy;

    RACont idxCont;
    if (mergeInsertion(copy, idxCont) == 1)
        throw std::runtime_error("reached max jacobsthalValue while inserting groups");

    RACont ret;
    for (iterator it = idxCont.begin(); it != idxCont.end(); ++it)
        ret.push_back(copy[*it]);

    std::cout << "Number of comparisons: " << _numCompar << std::endl;
    return (ret);
}

template <typename RACont>
bool PmergeMe::mergeInsertion( RACont& inputCont, RACont& resCont, std::size_t step ) {
    typedef typename RACont::iterator iterator;
    std::size_t size = inputCont.size() / step;

    //base case
    if (size == 1) {
        for (iterator it = inputCont.begin(); it != inputCont.end(); ++it)
            std::cout << *it << " ";
        std::cout << std::endl;
        resCont.push_back(0);
        _chainSize++;
        return (0);
    }

    bool hasOddElem = size % 2 == 1;


    //split into pairs (bigger, smaller)
    for (iterator it = inputCont.begin(); it < inputCont.end() - step * (1 + hasOddElem); it += 2 * step) {
        if (compare(*it, *(it + step)) == -1) {
            if (step != 1)
                std::swap_ranges(it, it + step, it + step);
            else
                std::iter_swap(it, it + step);
        }
    }

    //recursive call
    if (mergeInsertion(inputCont, resCont, step * 2) == 1)
        return (1);
    
    std::vector<int> pend;
    pend.reserve(resCont.size() + hasOddElem); //cannot be bigger than that
    

    //std::cout << "step is " << step << "and *resCont.begin() + step  is " << *resCont.begin() + step << std::endl;
    resCont.insert(resCont.begin(), *resCont.begin() + step); //smaller counterpart of smallest element in sorted chain
    _chainSize++;
    for (iterator it = resCont.begin() + 2; it != resCont.end(); ++it)
            pend.push_back(*it + step); //get idx of a loser counterpart
    if (hasOddElem){
        pend.push_back((size - 1) * step);
        std::cout << "has odd elem " << inputCont[(size - 1) * step] << std::endl;
    }

    std::cout << "Main chain is: ";
    for (iterator it = resCont.begin(); it != resCont.end(); ++it)
        std::cout << inputCont[*it] << " ";

    std::cout << "\nPending elments: ";
    for (std::vector<int>::iterator it = pend.begin(); it != pend.end(); ++it)
        std::cout << inputCont[*it] << " ";
    std::cout << std::endl;

    if (insert_group(inputCont, resCont, pend, 0, 0) == 1)
        return (1);
    return (0);
}



template <typename RACont>
bool PmergeMe::insert_group(RACont& Cont, RACont& chain, std::vector<int>& pend, std::size_t prev_end, std::size_t round)
{
    bool last_round = false;

    if (!pend.size())
        return (0);

    if (round == 32)
        return (1);

    std::size_t end_idx = prev_end + _jacobsthalValues[round];

    if (pend.size() <= end_idx) {
        end_idx = pend.size();
        last_round = true;
    }
   
    std::cout << "end_idx is " << end_idx << std::endl;
    (void)chain;

    for (int idx = (int)end_idx - 1; idx >= (int)prev_end; --idx) {

        int pend_val = Cont[pend[idx]];
        std::cout << "inserting " << pend_val << std::endl;
    
        std::size_t found_chain_pos = binary_search(Cont, chain, pend_val, 0, pow(2, round + 2) - 1);

        if (found_chain_pos == _chainSize)
            chain.push_back(pend[idx]);
        else if (found_chain_pos > _chainSize)
            std::cerr << "sth went wrong" <<std::endl;
        else 
            chain.insert(chain.begin() + found_chain_pos, pend[idx]); //for deque though push_front is possible..
        _chainSize++;

        typedef typename RACont::iterator iterator;
        std::cout << "Main chain is: ";
        for (iterator it = chain.begin(); it != chain.end(); ++it)
            std::cout << Cont[*it] << " ";
        std::cout << std::endl;
    }
    if (!last_round)
        return (insert_group(Cont, chain, pend, end_idx, round + 1));
    return (0);
}

template <typename RACont>
std::size_t PmergeMe::binary_search( RACont& Cont, RACont& chain, int pend_val, std::size_t start, std::size_t end) {
    
    if (start == end)
        return (start);

    if (end > _chainSize)
        end = _chainSize;

    std::size_t mid = start + (end - start) / 2;

    std::cout << "mid is " << mid << " end is " << end << std::endl; 
    
    switch (compare(pend_val, Cont[chain[mid]])) {
        case 0: return (mid);
        case 1:
            std::cout << "bigger than" << std::endl; 
            return (binary_search(Cont, chain, pend_val, mid + 1, end));
        case -1:
            std::cout << "smaller than" << std::endl;  
            return (binary_search(Cont, chain, pend_val, start, mid));
        default: throw std::runtime_error("Sth went wrong");
    }

}