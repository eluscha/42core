#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

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

    PresidentialPardonForm PPForm("Max");
    Nancy.executeForm(PPForm);
    Joe.signForm(PPForm);
    Bureaucrat Ross("Ross", 5);
    Ross.executeForm(PPForm);
    Ross.signForm(PPForm);
    Ross.executeForm(PPForm);

    AForm *PPFptr = new PresidentialPardonForm("someone");
    Ross.signForm(*PPFptr);
    Ross.executeForm(*PPFptr);

    delete PPFptr;
}