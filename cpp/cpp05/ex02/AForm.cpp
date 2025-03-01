#include "AForm.hpp"
#include "Bureaucrat.hpp"

//Constructors
AForm::AForm( const std::string& name, int grade_sign, int grade_exec )
    : _name(name), _issigned(false), _grade_sign(grade_sign), _grade_exec(grade_exec)
{
    if (grade_sign > 150)
        throw GradeTooLowException();
    else if (grade_sign < 1)
        throw GradeTooHighException();

    if (grade_exec > 150)
        throw GradeTooLowException();
    else if (grade_exec < 1)
        throw GradeTooHighException();
}

AForm::AForm( const AForm& other )
    : _name(other._name), _issigned(false), _grade_sign(other._grade_sign), _grade_exec(other._grade_exec)
{
    if (_grade_sign > 150)
        throw GradeTooLowException();
    else if (_grade_sign < 1)
        throw GradeTooHighException();

    if (_grade_exec > 150)
        throw GradeTooLowException();
    else if (_grade_exec < 1)
        throw GradeTooHighException();
}

//Destructors
AForm::~AForm() {}

//Overloaded operators
AForm& AForm::operator=( const AForm& other )
{
    if (this == &other)
        return (*this);
    return (*this); //not clear yet what should be done here
}

std::ostream& operator<<( std::ostream& o, const AForm& frm )
{
    o << frm.getName();
    //o << ", " << (frm.getIsSigned() ? "signed" : "not signed");
    o << ", grade to sign " << frm.getGradeSign();
    o << ", grade to execute " << frm.getGradeExec();
    return (o);
}

//Getters
std::string AForm::getName() const
{
    return (_name);
}

bool AForm::getIsSigned() const
{
    return (_issigned);
}

int AForm::getGradeSign() const
{
    return (_grade_sign);
}
    
int AForm::getGradeExec() const
{
    return (_grade_exec);
}

//Public Methods
bool AForm::beSigned( const Bureaucrat& brcrt )
{
    if (_issigned)
        return (0);
    if (brcrt.getGrade() <= _grade_sign)
        return (_issigned = true, 1);
    throw AForm::GradeTooLowException();
}

//Exception Method Overrides
std::string AForm::GradeTooLowException::_msg = "Form: Grade too low";

const char* AForm::GradeTooLowException::what() const throw()
{
    return _msg.c_str();
}

std::string AForm::GradeTooHighException::_msg = "Form: Grade too high";

const char* AForm::GradeTooHighException::what() const throw()
{
    return _msg.c_str();
}
