#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <limits.h>
#include <float.h>
#include <cmath>

class ScalarConverter
{
private:
    //Constructors
    ScalarConverter();
    ScalarConverter( const ScalarConverter& other );

    //Destructors
    ~ScalarConverter();

    //Overloaded operators
    ScalarConverter& operator=( const ScalarConverter& other );

public:
    //Static public methods
    static void convert( const std::string& input );

};