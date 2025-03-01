#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

//Constructors
ShrubberyCreationForm::ShrubberyCreationForm( const std::string& target )
    : AForm("Schrubbery_at_" + target, 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm( const ShrubberyCreationForm& other )
    : AForm(other), _target(other._target) {}

//Destructors
ShrubberyCreationForm::~ShrubberyCreationForm() {}

//Overloaded operators
ShrubberyCreationForm& ShrubberyCreationForm::operator=( const ShrubberyCreationForm& other )
{
    if (this == &other)
        return (*this);
    return (*this); //what shell be done ? should target not be const ? then not in the form name ?
}

//Virtual Function override
void ShrubberyCreationForm::execute( Bureaucrat const& executor ) const
{
    if (executor.getGrade() != 1)
        return ;
    
    std::cout << " \n \
         cccc       ccccccc        cccc       cccc \n \
       cccccccc    ccccccccccc    ccccccc    ccccccc \n \
     ccccccccccc   ccccccccccc   ccccccccc  ccccccccc \n \
       cccccccc     ccccccccc     ccccccc    ccccccc \n \
          ||           ||           ||         || \n \
          ||           ||           ||         || \n \
    \n \
   SSSSS  H   H  RRRRR  U   U  BBBBB  BBBBB  EEEEE  RRRRR  Y   Y \n \
   S      H   H  R   R  U   U  B    B B    B E      R   R  Y   Y \n \
   SSSSS  HHHHH  RRRRR  U   U  BBBBB  BBBBB  EEEEE  RRRRR   YYY \n \
       S  H   H  R  R   U   U  B    B B    B E      R  R     Y \n \
   SSSSS  H   H  R   R   UUU   BBBBB  BBBBB  EEEEE  R   R    Y \n \
    " << std::endl;
}

