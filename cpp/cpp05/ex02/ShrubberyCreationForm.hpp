#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm
{
    const std::string _target;
    
    //Private Constructors
    ShrubberyCreationForm();

public:
    //Public Constructors
    ShrubberyCreationForm( const std::string& target );
    ShrubberyCreationForm( const ShrubberyCreationForm& other );

    //Destructors
    ~ShrubberyCreationForm();

    //Overloaded operators
    ShrubberyCreationForm& operator=( const ShrubberyCreationForm& other );

    //Virtual Function override
    bool execute( Bureaucrat const& executor ) const;
};