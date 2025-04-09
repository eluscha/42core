#pragma once

#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>

class RPN {
private:
    std::stack<int> _stck;

    //Private methods
    void performOperation( char c );

public:
    // Orthdox Canoncial Form
    RPN( void );
    RPN( const RPN& other );
    ~RPN();
    RPN& operator=( const RPN& other );

    // Public Methods
    void evaluateExpression( std::string& input );

};