#include "BitcoinExchange.hpp"

// Orthdox Canoncial Form
BitcoinExchange::BitcoinExchange( void ) {}

BitcoinExchange::BitcoinExchange( const BitcoinExchange& other ) 
    :  _dbRates(other._dbRates) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange& other ) {
    if (this != &other)
        _dbRates = other._dbRates;
    return (*this);
}

// Public Methods
void BitcoinExchange::loadDB( std::string path ) {
    std::ifstream file(path.c_str());
    if (!file)
        throw std::runtime_error("Failed to open file: " + path);
    
    std::string line;

    if (!std::getline(file, line))
        throw std::runtime_error("Database " + path + " is empty."); 

    while (std::getline(file, line)) {
        std::size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            std::string date = line.substr(0, commaPos);
            std::string rateStr = line.substr(commaPos + 1);
            double rate = std::atof(rateStr.c_str()); // Caution: 0 if conversion with atof was impossible
            _dbRates[date] = rate; // Caution: will overwrite previous value, if the date was there already
        }
    }
}

static double get_price( std::string& line, std::size_t start );

void BitcoinExchange::readInput( std::string& path ) {
    std::ifstream file(path.c_str());
    if (!file)
        throw std::runtime_error("Failed to open input file.");
    
    std::string line;
    std::string searchKey;
    double price;

    std::getline(file, line);
    if (line != "date | value")
        throw std::runtime_error("Input file has incorrect header.");
    while (std::getline(file, line)) {
        std::size_t sepPos = line.find(" | ");
        if (sepPos != std::string::npos) {
            searchKey = line.substr(0, sepPos);
            
            try {
                price = get_price(line, sepPos + 3);
                std::map<std::string, double>::iterator it = _dbRates.find(searchKey);
                if (it != _dbRates.end())
                    std::cout << searchKey << " => " << it->second << " = " <<  it->second * price << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }

        }
    }
}

// static helpers
double get_price( std::string& line, std::size_t start ) {
    std::stringstream ss;
    ss << line.substr(start);
    double price;
    ss >> price;
    if (ss.fail())
        throw std::runtime_error("not a number.");
    else if (price > 1000)
        throw std::runtime_error("not a positive number.");
    else if (price < 0)
        throw std::runtime_error("too large a number.");
    return (std::atof(line.substr(start).c_str()));
}