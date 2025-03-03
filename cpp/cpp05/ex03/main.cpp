#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main()
{
    Intern student;

    AForm *form = student.makeForm("ShrubberyCreationForm", "home");
    
    Bureaucrat Nancy("Nancy", 100);
    Nancy.signForm(*form);
    //Nancy.executeForm(*form);

    delete form;

    form = student.makeForm("RobotomyRequestForm", "mouse");
    Nancy.signForm(*form);
    Nancy.executeForm(*form);
    form->beSigned(Bureaucrat(1));
    form->execute(Bureaucrat(1));
    delete form;

}