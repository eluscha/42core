#include "ScalarConverter.hpp"

//Constructors
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter( const ScalarConverter& other ) 
{
    (void)other;
}

//Destructors
ScalarConverter::~ScalarConverter() {}

//Overloaded operators
ScalarConverter& ScalarConverter::operator=( const ScalarConverter& other )
{
    (void)other;
    return (*this);
}

//ScalarConverter::convert and its helpers

static void charConvert( const std::string& input );
static bool numConvert( const std::string& input );
static void nanConvert( void );
static bool infConvert( const std::string& input );
static bool intConvert( const std::string& input );
static bool floatConvert( const std::string& input );
static bool doubleConvert( const std::string& input );
static void printChar( char c );

void ScalarConverter::convert( const std::string& input )
{
    bool err = 0;
    if (!std::isdigit(input[0]))
    {
        if (input.length() == 1)
            charConvert(input);
        else if (input[0] == '-' || input[0] == '+')
            err = numConvert(input);
        else if (input == "nan" || input == "nanf")
            nanConvert();
        else
            err = 1;
    }
    else 
        err = numConvert(input);
    if (err)
        std::cerr << "Error: conversion impossible" << std::endl; 
}

//helpers for ScalarConverter::convert
void charConvert( const std::string& input )
{
    int myInt = static_cast<int>(input[0]);

    std::cout << "char: '" << input[0] << "'" << std::endl;
    std::cout << "int: " << myInt << std::endl;
    std::cout << "float: " << myInt << ".0f" << std::endl;
    std::cout << "double: " << myInt << ".0" << std::endl;
}

bool numConvert( const std::string& input )
{
    if (input.find("inf", 1) != std::string::npos)
        return (infConvert(input));
    else if (input.find('.', 1) == std::string::npos)
        return (intConvert(input));
    else if (input[input.length() - 1] == 'f')
        return (floatConvert(input));
    else
        return (doubleConvert(input));
}

void nanConvert()
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: " << "nanf" << std::endl;
    std::cout << "double: " << "nan" << std::endl;
}

bool infConvert( const std::string& input )
{
    if (input.compare(1, 3, "inf") != 0 || input[input.length() - 1] != 'f')
        return (1);
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: " << input[0] << "inff" << std::endl;
    std::cout << "double: " << input[0] << "inf" << std::endl;
    return (0);
}

bool intConvert( const std::string& input )
{
    std::stringstream ss;
    int myInt;
    ss << input;
    ss >> myInt;
    if (ss.fail())
        return (1);
    printChar(static_cast<char>(myInt));
    std::cout << "int: " << myInt << std::endl;
    std::cout << "float: " << static_cast<float>(myInt) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(myInt) << ".0" << std::endl;
    return (0);
}

bool floatConvert( const std::string& input )
{
    std::stringstream ss;
    float myFloat;
    ss << input;
    ss >> myFloat;
    if (ss.fail())
        return (1);

    if (static_cast<int>(myFloat) == myFloat)
        std::cout << std::fixed << std::setprecision(1); 
    
    printChar(static_cast<char>(myFloat));
    std::cout << "int: " << static_cast<int>(myFloat) << std::endl;
    std::cout << "float: " << myFloat << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(myFloat) << std::endl;
    return (0);
}
bool doubleConvert( const std::string& input )
{
    std::stringstream ss;
    double myDouble;
    ss << input;
    ss >> myDouble;
    if (ss.fail())
        return (1);
        
    if (static_cast<int>(myDouble) == myDouble)
        std::cout << std::fixed << std::setprecision(1); 

    printChar(static_cast<char>(myDouble));
    std::cout << "int: " << static_cast<int>(myDouble) << std::endl;
    std::cout << "float: " << static_cast<float>(myDouble) << "f" << std::endl;
    std::cout << "double: " << myDouble << std::endl;
    return (0);
}
void printChar( char c )
{
    if (c < 0 || c > 127)
		std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(c))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << c << "'" << std::endl;
}