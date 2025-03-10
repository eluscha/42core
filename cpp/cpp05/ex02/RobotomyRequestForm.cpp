#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

//Constructors
RobotomyRequestForm::RobotomyRequestForm( const std::string& target )
    : AForm("Robotomy Request", 72, 45), _target(target) {}

RobotomyRequestForm::RobotomyRequestForm( const RobotomyRequestForm& other )
    : AForm(other), _target(other._target) {}

//Destructors
RobotomyRequestForm::~RobotomyRequestForm() {}

//Overloaded operators
RobotomyRequestForm& RobotomyRequestForm::operator=( const RobotomyRequestForm& other )
{
    if (this == &other)
        return (*this);
    //nothing to reassign
    return (*this); 
}

//Virtual Function override
bool RobotomyRequestForm::execute( Bureaucrat const& executor ) const
{
    if (!AForm::execute(executor))
        return (0);
    // Get a different random number each time the program runs
    srand(time(0));
    // Generate a random number between 0 and 100
    if (rand() % 2)
        std::cout << _target << " has been robotomized" << std::endl;
    else   
        std::cout << "Robotomy of " << _target << " has failed." << std::endl;
    return (1);
}

