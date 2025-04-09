#include "RPN.hpp"

int main(int argc, char **argv){
    if (argc != 2) {
        std::cerr << "Usage: ./RPN <input_string>" << std::endl;
        return (1);
    }
    std::string input = argv[1];
    RPN test;
    try {
        test.evaluateExpression(input);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}