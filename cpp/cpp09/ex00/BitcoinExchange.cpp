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
            it = _dbRates.upper_bound(date);
            if (it == _dbRates.begin())
                std::cout << "No earlier date available for " << date << std::endl;
            else {
                --it;
                std::cout << date << " => " << price << " = " <<  it->second * price << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
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
    return (price);
}

std::string get_date( std::string& line, std::size_t end ) {
    std::string date = line.substr(0, end);
    if (!is_valid_date(date))
        throw std::runtime_error("not a valid date.");
    return (date);
}

bool    is_valid_date( const std::string& date ) {

    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30, 31 };

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

    int year = std::atoi(yearStr.c_str());
    int month = std::atoi(monthStr.c_str());
    int day = std::atoi(dayStr.c_str());

    if (month < 1 || month > 12 || day < 1) return (false);

    int maxDay = daysInMonth[month - 1];

    if (month == 2) {
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
            maxDay = 29;
    }
    return (day <= maxDay);
}
