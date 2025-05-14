#include "BitcoinExchange.hpp"

int main(int argc, char **argv){
    if (argc > 2) {
        std::cerr << "Usage: ./btc <input_file_with_prices>" << std::endl;
        return (1);
    }
    std::string inputPath;
    if (argc != 1)
        inputPath = argv[1];

    BitcoinExchange BE;
    try {
        BE.loadDB();
        BE.readInput(inputPath);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return (1);
    }
    return (0);
}