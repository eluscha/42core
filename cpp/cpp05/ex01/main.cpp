#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    Form highgrade("HighGradeForm", 2, 1);
    Form lowgrade("lowGradeForm", 150, 149);

    Bureaucrat brcrts[5];
    int grades[] = {150, 149, 100, 2, 1};
    for (int i = 0; i < 5; i++)
    {
        brcrts[i] = Bureaucrat(grades[i]);
        brcrts[i].signForm(highgrade);
        brcrts[i].signForm(lowgrade);
    }
    
    try
    {
        Form("WeirdForm", 1, 0);
    }
    catch (std::exception& e) 
    {
        std::cout << "Caught an exception: " << e.what() << std::endl;
    }
}