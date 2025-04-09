#include "RPN.hpp"

// Orthdox Canoncial Form
RPN::RPN( void ) {}

RPN::RPN( const RPN& other ) 
    :  _stck(other._stck) {}

RPN::~RPN() {}

RPN& RPN::operator=( const RPN& other ) {
    if (this != &other)
        _stck = other._stck;
    return (*this);
}

void RPN::evaluateExpression( std::string& input ) {
    size_t i = 0;
    char c;
    std::string numStr;
    int num;
    while (i < input.size()) {
        c = input[i];
        if (isdigit(c)) {
            numStr = input.substr(i);
            num = atoi(numStr.c_str());
            if (num > 9)
                throw std::runtime_error("number bigger than 9.");
            _stck.push(num);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
            performOperation(c);
        else if (!isspace(c))
            throw std::runtime_error("unknown token.");
        i++;
    }
    if (_stck.size() != 1)
        throw std::runtime_error("cannot evaluate expression.");   
    std::cout << _stck.top() << std::endl;
}

void RPN::performOperation( char c ) {
    int vals[2];
    for (int i = 0; i < 2; ++i) {
        if (_stck.empty())
            throw std::runtime_error("cannot get top of empty stack.");
        vals[i] = _stck.top();
        _stck.pop();
    }
    //std::cout << "vals: " << vals[0] << ' ' << vals[1] << std::endl;
    if (c == '+')
        _stck.push(vals[1] + vals[0]);
    else if (c == '-')
        _stck.push(vals[1] - vals[0]);
    else if (c == '*')
        _stck.push(vals[1] * vals[0]);    
    else
        _stck.push(vals[1] / vals[0]);
}