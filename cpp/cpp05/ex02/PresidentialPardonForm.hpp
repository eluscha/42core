#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
    const std::string _target;
    
    //Private Constructors
    PresidentialPardonForm();

public:
    //Public Constructors
    PresidentialPardonForm( const std::string& target );
    PresidentialPardonForm( const PresidentialPardonForm& other );

    //Destructors
    ~PresidentialPardonForm();

    //Overloaded operators
    PresidentialPardonForm& operator=( const PresidentialPardonForm& other );

    //Virtual Function override
    bool execute( Bureaucrat const& executor ) const;
};