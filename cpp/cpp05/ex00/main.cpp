#include "Bureaucrat.hpp"

int main()
{
    try
    {
        throw Bureaucrat::GradeTooLowException();
    }
    catch (std::exception& e) 
    {
        std::cout << "Caught an exception: " << e.what() << std::endl;
    }
}