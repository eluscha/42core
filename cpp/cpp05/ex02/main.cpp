#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"

int main()
{
    ShrubberyCreationForm SCForm("home");
    SCForm.execute(Bureaucrat("Nancy", 1));
    
}