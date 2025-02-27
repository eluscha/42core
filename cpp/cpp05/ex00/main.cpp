#include "Bureaucrat.hpp"

int main()
{
    Bureaucrat brcrt;
    int grades[] = {0, 1, 100, 150, 151};
    for (int i = 0; i < (int)(sizeof(grades)/sizeof(int)); i++)
    {
        try
        {
            brcrt = Bureaucrat(grades[i]);
        }
        catch (std::exception& e) 
        {
            std::cout << "Caught an exception: " << e.what() << std::endl;
        }

        std::cout << "Bureaucrat " << i << ": " << brcrt << std::endl;
        
        try
        {
            if (brcrt.getGrade() == 1)
                brcrt.incrementGrade();
            else
                brcrt.decrementGrade();
        }
        catch (std::exception& e) 
        {
            std::cout << "Caught an exception: " << e.what() << std::endl;
        }

        std::cout << "Bureaucrat " << i << ": " << brcrt << std::endl;        
    }
}