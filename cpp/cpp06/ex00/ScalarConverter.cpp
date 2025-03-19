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

static void charConvert( char c );
static bool numConvert( const std::string& input );
static bool nanConvert( const std::string& input );
static bool infConvert( const std::string& input );
static bool intConvert( int num );
static bool floatConvert( float num );
static bool doubleConvert( double num );
static void printChar( int num );

void ScalarConverter::convert( const std::string& input )
{
    bool err = 0;
    if (!std::isdigit(input[0]))
    {
        if (input.length() == 1)
            charConvert(input[0]);
        else if (input[0] == '-' || input[0] == '+')
            err = numConvert(input);
        else if (input.find("nan") != std::string::npos)
            nanConvert(input);
        else
            err = 1;
    }
    else 
        err = numConvert(input);
    if (err)
        std::cerr << "Error: conversion impossible" << std::endl; 
}

//helpers for ScalarConverter::convert
void charConvert( char c )
{
    std::cout << std::fixed << std::setprecision(1); 
    std::cout << "char: '" << c << '\'' << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << static_cast<float>(c) << 'f' << std::endl;
    std::cout << "double: " << static_cast<double>(c) << std::endl;
}

bool numConvert( const std::string& input )
{
    std::stringstream ss;

    if (input.find("inf", 1) != std::string::npos)
        return (infConvert(input));

    ss << input;
    if (input.find('.', 1) == std::string::npos)
    {
        int num;
        ss >> num;
        if (!ss.fail())
            return (intConvert(num));
    }
    else if (input[input.length() - 1] == 'f')
    {
        float num;
        ss >> num;
        if (!ss.fail())
            return (floatConvert(num));
    }
    else
    {
        double num;
        ss >> num;
        if (!ss.fail())
            return (doubleConvert(num));
    }
    return (1);
}

bool nanConvert( const std::string& input )
{
    float nanf;
    double nan;

    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    if (input == "nanf") 
    {
        nanf = NAN;
        
        std::cout << "float: " << nanf << 'f' << std::endl;
        std::cout << "double: " << static_cast<double>(nanf) << std::endl;
        return (0);
    }
    else if (input == "nan")
    {
        nan = NAN;

        std::cout << "float: " << static_cast<float>(nan) << 'f' << std::endl;
        std::cout << "double: " << nan << std::endl;
        return (0);
    }
    return (1);
}

bool infConvert( const std::string& input )
{
    float inff;
    double inf;
    int sign = (input[0] == '+'? 1 : -1);

    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    if (input.length() == 5 && input.find("inff", 1, 4) != std::string::npos) 
    {
        inff = sign * std::numeric_limits<float>::infinity();
        
        std::cout << "float: " << inff << 'f' << std::endl;
        std::cout << "double: " << static_cast<double>(inff) << std::endl;
        return (0);
    }
    else if (input.length() == 4 && input.find("inf", 1, 3) != std::string::npos)
    {
        inf = sign * std::numeric_limits<double>::infinity();
        std::cout << "float: " << static_cast<float>(inf) << 'f' << std::endl;
        std::cout << "double: " << inf << std::endl;
        return (0);
    }
    return (1);
}

bool intConvert( int num )
{
    printChar(static_cast<char>(num));
    std::cout << std::fixed << std::setprecision(1); 
    std::cout << "int: " << num << std::endl;
    std::cout << "float: " << static_cast<float>(num) << 'f' << std::endl;
    std::cout << "double: " << static_cast<double>(num) << std::endl;
    return (0);
}

bool floatConvert( float num )
{
    int asInt = static_cast<int>(num);

    if (num >= pow(2, 31) || num < -1 * pow(2,31))
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
    }
    else
    {
        asInt = static_cast<int>(num); 
        printChar(asInt);
        std::cout << "int: " << asInt << std::endl;
    }

    if (std::fmod(num, 1.0f) == 0.0f)
        std::cout << std::fixed << std::setprecision(1); 
    
    std::cout << "float: " << num << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(num) << std::endl;
    return (0);
}
bool doubleConvert( double num )
{
    int asInt;

    if (std::fmod(num, 1.0) == 0.0)
        std::cout << std::fixed << std::setprecision(1);

    if (num >= pow(2, 31) || num < INT_MIN)
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
    }
    else
    {
        asInt = static_cast<int>(num);
        printChar(asInt);
        std::cout << "int: " << asInt << std::endl;
    }

    if (num > FLT_MAX || num < -FLT_MAX)
        std::cout << "float: impossible" << std::endl;
    else
        std::cout << "float: " << static_cast<float>(num) << "f" << std::endl;

    std::cout << "double: " << num << std::endl;
    return (0);
}
void printChar( int num )
{
    if (num < 0 || num > 127)
		std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(num))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(num) << '\'' << std::endl;
}