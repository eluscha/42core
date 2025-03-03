#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"

int main()
{
    ShrubberyCreationForm SCForm("home");
    Bureaucrat Nancy("Nancy", 73);
    Nancy.signForm(SCForm);
    Nancy.signForm(SCForm);
    Nancy.signForm(SCForm);
    Nancy.executeForm(SCForm);

    AForm *SCFptr = new ShrubberyCreationForm("garden");
    Nancy.signForm(*SCFptr);
    Nancy.executeForm(*SCFptr);

    delete SCFptr;

    RobotomyRequestForm RRForm("sth");
    Nancy.executeForm(RRForm);
    Nancy.signForm(RRForm);
    Nancy.executeForm(RRForm);
    Bureaucrat Joe("Joe", 12);
    Joe.signForm(RRForm);
    Joe.executeForm(RRForm);

    
}