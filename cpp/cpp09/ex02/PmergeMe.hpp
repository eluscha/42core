#pragma once

#include <iostream>
#include <list>
#include <vector>


class PmergeMe {
private:

    static const std::size_t _jacobsthalValues[];
    std::size_t _chainSize;
    //Private methods tenmplates
    template <typename RACont>
    bool mergeInsertion( RACont& inputCont, RACont& resCont, std::size_t step = 1);

    template <typename RACont>
    bool insert_group(RACont& Cont, RACont& chain, std::vector<int>& pend, std::size_t prev_end, std::size_t round);

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

    if (copy.size() < 2)
        return copy;

    RACont idxCont;
    if (mergeInsertion(copy, idxCont) == 1)
        throw std::runtime_error("reached max jacobsthalValue while inserting groups");

    RACont ret;
    for (iterator it = idxCont.begin(); it != idxCont.end(); ++it)
        ret.push_back(copy[*it]);

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
        if (*it < *(it + step)) {
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
    typedef typename RACont::iterator iterator;
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
        std::cout << "inserting " << Cont[pend[idx]] <<std::endl;
        bool found = false;

        for (iterator itc = chain.begin(); itc != chain.end(); ++itc) {
            std::cout << "comparing " << Cont[pend[idx]] << " to " << Cont[*itc] << std::endl;
            if (Cont[pend[idx]] < Cont[*itc] ) {
                chain.insert(itc, pend[idx]); //for deque though push_front is possible..
                found = true;
                break ;
            }
        }
        if (!found)
            chain.push_back(pend[idx]);
        _chainSize++;
    }
    if (!last_round)
        return (insert_group(Cont, chain, pend, end_idx, round + 1));
    return (0);
}