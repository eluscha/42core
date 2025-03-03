#include "AForm.hpp"
#include <cstdlib>

class RobotomyRequestForm : public AForm
{
    const std::string _target;
    
    //Private Constructors
    RobotomyRequestForm();

public:
    //Public Constructors
    RobotomyRequestForm( const std::string& target );
    RobotomyRequestForm( const RobotomyRequestForm& other );

    //Destructors
    ~RobotomyRequestForm();

    //Overloaded operators
    RobotomyRequestForm& operator=( const RobotomyRequestForm& other );

    //Virtual Function override
    bool execute( Bureaucrat const& executor ) const;
};