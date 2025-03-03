#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

//Constructors
PresidentialPardonForm::PresidentialPardonForm( const std::string& target )
    : AForm("Presidential Pardon", 25, 5), _target(target) {}

PresidentialPardonForm::PresidentialPardonForm( const PresidentialPardonForm& other )
    : AForm(other), _target(other._target) {}

//Destructors
PresidentialPardonForm::~PresidentialPardonForm() {}

//Overloaded operators
PresidentialPardonForm& PresidentialPardonForm::operator=( const PresidentialPardonForm& other )
{
    if (this == &other)
        return (*this);
    return (*this); //what shell be done ? should target not be const ? then not in the form name ?
}

//Virtual Function override
bool PresidentialPardonForm::execute( Bureaucrat const& executor ) const
{
    if (!AForm::execute(executor))
        return (0);
    std::cout << _target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
    return (1);
}

