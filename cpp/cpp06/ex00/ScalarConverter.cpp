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

//Static public methods
static void charConvert( const std::string& input );
static bool numConvert( const std::string& input );
static void nanConvert( void );
static bool infConvert( const std::string& input );
static bool intConvert( const std::string& input );
//static void floatConvert( const std::string& input );
//static void doubleConvert( const std::string& input );
void ScalarConverter::convert( const std::string& input )
{
    bool err = 0;
    if (!std::isdigit(input[0]))
    {
        if (input.length() == 1)
            charConvert(input);
        else if (input[0] == '-' || input[0] == '+')
            err = numConvert(input);
        else if (input.find("nan", 0) != std::string::npos)
            nanConvert();
        else
            err = 1;
    }
    else 
        err = numConvert(input);
    if (err)
        std::cerr << "Error: invalid input" << std::endl; 
}

//helpers for ScalarConverter::convert
void charConvert( const std::string& input )
{
    int myInt = static_cast<int>(input[0]);

    std::cout << "Char: " << input[0] << std::endl;
    std::cout << "Int: " << myInt << std::endl;
    std::cout << "Float: " << myInt << ".0f" << std::endl;
    std::cout << "Double: " << myInt << ".0" << std::endl;
}

bool numConvert( const std::string& input )
{
    if (input.find("inf", 1) != std::string::npos)
        return (infConvert(input));
    else if (input.find('.', 1) == std::string::npos)
        return (intConvert(input));
    return (0);
}

void nanConvert()
{
    std::cout << "Char: " << "impossible" << std::endl;
    std::cout << "Int: " << "impossible" << std::endl;
    std::cout << "Float: " << "nanf" << std::endl;
    std::cout << "Double: " << "nan" << std::endl;
}

bool infConvert( const std::string& input )
{
    if (input.length() != 4 && input.length() != 5)
        return (1);
    if (input[input.length() - 1] != 'f')
        return (1);
    std::cout << "Char: " << "impossible" << std::endl;
    std::cout << "Int: " << "impossible" << std::endl;
    std::cout << "Float: " << input[0] << "inff" << std::endl;
    std::cout << "Double: " << input[0] << "inf" << std::endl;
    return (0);
}

bool intConvert( const std::string& input )
{
    std::stringstream ss;
    int myInt;
    ss << input;
    ss >> myInt;
    if (std::isprint(myInt))
        std::cout << "Char: " << static_cast<char>(myInt) << std::endl;
    else
        std::cout << "Char: " << "Impossible" << std::endl;
    std::cout << "Int: " << myInt << std::endl;
    std::cout << "Float: " << myInt << ".0f" << std::endl;
    std::cout << "Double: " << myInt << ".0" << std::endl;
    return (0);
}

//static void floatConvert( const std::string& input );
//static void doubleConvert( const std::string& input );