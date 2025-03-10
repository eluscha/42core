#include "Bureaucrat.hpp"

//Constructors
Bureaucrat::Bureaucrat() : _name("noname"), _grade(150) 
{
    std::cout << "Default Bureaucrat constructor is called" << std::endl;
}

Bureaucrat::Bureaucrat( int grade ) : _name("noname"), _grade(150)
{
    std::cout << "Bureaucrat parametrized constructor is called with grade = " << grade << std::endl;
    if (grade > 150)
        throw GradeTooLowException();
    else if (grade < 1)
        throw GradeTooHighException();
    else
        _grade = grade;
}

Bureaucrat::Bureaucrat( const std::string& name ) : _name(name), _grade(150) 
{
    std::cout << "Bureaucrat parametrized constructor is called" << std::endl;
}

Bureaucrat::Bureaucrat( const std::string& name, int grade ) : _name(name), _grade(150)
{
    std::cout << "Bureaucrat parametrized constructor is called with grade = " << grade << std::endl;
    if (grade > 150)
        throw GradeTooLowException();
    else if (grade < 1)
        throw GradeTooHighException();
    else
        _grade = grade;
}

Bureaucrat::Bureaucrat( const Bureaucrat& other ) : _name(other._name), _grade(other._grade) {}

//Destructors
Bureaucrat::~Bureaucrat() {}

//Overloaded operators
Bureaucrat& Bureaucrat::operator=( const Bureaucrat& other )
{
    if (this == &other)
        return (*this);
    _grade = other._grade;
    return (*this);
}

std::ostream& operator<<( std::ostream& o, const Bureaucrat& brcrt )
{
    o << brcrt.getName() << ", bureaucrat grade " << brcrt.getGrade();
    return (o);
}

//Getters
std::string Bureaucrat::getName() const
{
    return (_name);
}

int Bureaucrat::getGrade() const
{
    return (_grade);
}

//Public Methods
void Bureaucrat::incrementGrade()
{
    std::cout << "Incrementing the grade for " << *this << std::endl;
    if (_grade == 1)
        throw GradeTooHighException();
    else
        _grade--;
}

void Bureaucrat::decrementGrade()
{
    std::cout << "Decrementing the grade for " << *this << std::endl;
    if (_grade == 150)
        throw GradeTooLowException();
    else
        _grade++;
}

//Exception Constructors and Method Overrides
std::string Bureaucrat::GradeTooLowException::_msg = "The smallest possible grade is 150.";

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
    return _msg.c_str();
}

std::string Bureaucrat::GradeTooHighException::_msg = "The highest possible grade is 1.";

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
    return _msg.c_str();
}
