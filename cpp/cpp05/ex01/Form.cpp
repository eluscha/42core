#include "Form.hpp"
#include "Bureaucrat.hpp"

//Constructors
Form::Form() : _name("noname"), _issigned(false), _grade_sign(150), _grade_exec(150) {}

Form::Form( const std::string& name, int grade_sign, int grade_exec )
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

Form::Form( const Form& other )
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
Form::~Form() {}

//Overloaded operators
Form& Form::operator=( const Form& other )
{
    if (this == &other)
        return (*this);
    //there is no attributes to reassign, only _issigned, but i do not think it makes sense
    return (*this);
}

std::ostream& operator<<( std::ostream& o, const Form& frm )
{
    o << frm.getName();
    o << ", grade to sign " << frm.getGradeSign();
    o << ", grade to execute " << frm.getGradeExec();
    return (o);
}

//Getters
std::string Form::getName() const
{
    return (_name);
}

bool Form::getIsSigned() const
{
    return (_issigned);
}

int Form::getGradeSign() const
{
    return (_grade_sign);
}
    
int Form::getGradeExec() const
{
    return (_grade_exec);
}

//Public Methods
bool Form::beSigned( const Bureaucrat& brcrt )
{
    if (_issigned)
        return (0);
    if (brcrt.getGrade() <= _grade_sign)
        return (_issigned = true, 1);
    throw Form::GradeTooLowException();
}

//Exception Method Overrides
std::string Form::GradeTooLowException::_msg = "Form: Grade too low";

const char* Form::GradeTooLowException::what() const throw()
{
    return _msg.c_str();
}

std::string Form::GradeTooHighException::_msg = "Form: Grade too high";

const char* Form::GradeTooHighException::what() const throw()
{
    return _msg.c_str();
}
