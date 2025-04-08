#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

class BitcoinExchange {
private:
    std::map<std::string, double> _dbRates;

public:
    // Orthdox Canoncial Form
    BitcoinExchange( void );
    BitcoinExchange( const BitcoinExchange& other );
    ~BitcoinExchange();
    BitcoinExchange& operator=( const BitcoinExchange& other );

    // Public Methods
    void loadDB( std::string path = "data.csv");
    void readInput( std::string& path );
};