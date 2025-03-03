#include "Intern.hpp"

//Constructors
Intern::Intern() {}
Intern::Intern( const Intern& other ) 
{
    (void)other;
}

//Destructors
Intern::~Intern() {}

//Overloaded operators
Intern& Intern::operator=( const Intern& other )
{
    (void)other;
    return (*this);
}

//Public Methods
AForm* Intern::makeForm( std::string name, std::string target) const
{
    std::cout << "Intern creates " << name << std::endl;
    if (name == "ShrubberyCreationForm")
        return (new ShrubberyCreationForm(target));
    else if (name == "RobotomyRequestForm")
        return (new RobotomyRequestForm(target));
    else if (name == "PresidentialPardonForm")
        return (new PresidentialPardonForm(target));
    std::cerr << "Name " << name << " does not match any form" << std::endl;
    return (NULL);
}