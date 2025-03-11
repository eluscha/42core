#pragma once

#include <iostream>
#include <sstream>

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