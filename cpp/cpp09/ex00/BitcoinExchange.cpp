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

// .loadDB() : Method for loading a CSV database with dates and exchange rates
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

// .readInput() : Method for reading input file line by line and search DB for every date
// with static helpers 
static size_t get_sep_position( std::string& line );
static double get_price( std::string& line, std::size_t start );
static std::string get_date( std::string& line, std::size_t end );
static bool is_valid_date( const std::string& date );

void BitcoinExchange::readInput( std::string& path ) {
    std::ifstream file(path.c_str());
    if (!file)
        throw std::runtime_error("Failed to open input file.");
    
    std::string line;
    std::size_t sepPos;
    std::string date;
    double price;

    std::getline(file, line);
    if (line != "date | value")
        throw std::runtime_error("Input file has incorrect header.");
    while (std::getline(file, line)) {
        try {
            sepPos = get_sep_position(line);
            price = get_price(line, sepPos + 3);
            date = get_date(line, sepPos);
            std::map<std::string, double>::iterator it;
            it = _dbRates.find(date);
            if (it != _dbRates.end())
                std::cout << date << " => " << price << " = " <<  it->second * price << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

// static helpers
size_t  get_sep_position( std::string& line ) {
    size_t pos = line.find(" | ");
    if (pos == std::string::npos)
        throw std::runtime_error("bad input => " + line);
    return (pos);
}

double  get_price( std::string& line, std::size_t start ) {
    std::stringstream ss;
    ss << line.substr(start);
    double price;
    ss >> price;
    if (ss.fail())
        throw std::runtime_error("not a number.");
    else if (price > 1000)
        throw std::runtime_error("too large a number.");
    else if (price < 0)
        throw std::runtime_error("not a positive number.");
    return (std::atof(line.substr(start).c_str()));
}

std::string get_date( std::string& line, std::size_t end ) {
    std::string date = line.substr(0, end);
    if (!is_valid_date(date))
        throw std::runtime_error("not a valid date.");
    return (date);
}

bool    is_valid_date( const std::string& date ) {
    if (date.length() != 10) return (false);
    if (date[4] != '-' || date[7] != '-') return (false);

    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);

    // Check digits only
    for (int i = 0; i < 4; ++i)
        if (!isdigit(yearStr[i])) return (false);
    for (int i = 0; i < 2; ++i)
        if (!isdigit(monthStr[i]) || !isdigit(dayStr[i])) return (false);

    int month = std::atoi(monthStr.c_str());
    int day = std::atoi(dayStr.c_str());

    if (month < 1 || month > 12) return (false);
    if (day < 1 || day > 31) return (false); //not calender accurate

    return true;
}
