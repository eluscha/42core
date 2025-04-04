#include "MutantStack.hpp"
#include <iostream>
#include <string>
#include <stack>

// int main()
// {
//     MutantStack<int> mstack;
//     mstack.push(5); //push_back() for lists
//     mstack.push(17); 
//     std::cout << mstack.top() << std::endl; //back() for lists
//     mstack.pop(); //pop_back() for lists
//     std::cout << mstack.size() << std::endl;
//     mstack.push(3);
//     mstack.push(5);
//     mstack.push(737);
//     mstack.push(0);
//     MutantStack<int>::iterator it = mstack.begin();
//     MutantStack<int>::iterator ite = mstack.end();
//     ++it;
//     --it;
//     while (it != ite)
//     {
//         std::cout << *it << std::endl;
//         ++it;
//     }
//     std::stack<int> s(mstack); 
//     return 0;
// }

int main() {
    MutantStack<std::string> mstack;
    mstack.push("hello");
    mstack.push("how you're doing?");
    mstack.push("buy!");
    std::cout << "Top of mstack: " << mstack.top() << std::endl;
    MutantStack<std::string> mstack2 = mstack;
    std::cout << "Top of mstack2: " << mstack2.top() << std::endl;
    mstack2.pop();
    std::cout << "Top of mstack2 after pop(): " << mstack2.top() << std::endl;
    std::cout << "Top of mstack: " << mstack.top() << std::endl;
    
    MutantStack<std::string> mstack3(mstack);
    for (MutantStack<std::string>::reverse_iterator it = mstack3.rbegin(); it != mstack3.rend(); ++it) {
        *it += " \\m/";
        std::cout << *it << std::endl;
    }
        
}