#pragma once

#include <iostream>

class Bureaucrat;

class AForm
{
    const std::string _name;
    bool  _issigned;
    const int _grade_sign;
    const int _grade_exec;

    //Private Constructors
    AForm();

public:
    //Public Constructors
    AForm( const std::string& name, int grade_sign, int grade_exec );
    AForm( const AForm& other );

    //Destructors
    virtual ~AForm();

    //Overloaded operators
    AForm& operator=( const AForm& other );

    //Getters
    std::string getName() const;
    bool getIsSigned() const;
    int getGradeSign() const;
    int getGradeExec() const;

    //Public Methods
    bool beSigned( const Bureaucrat& brcrt );

    //Pure Virtual function
    virtual void execute(Bureaucrat const & executor) const = 0;

    //Exceptions
	class GradeTooLowException : public std::exception
	{
        static std::string _msg;
	public:
		const char* what() const throw();
	};

    class GradeTooHighException : public std::exception
	{
        static std::string _msg;
	public:
		const char* what() const throw();
	};

};

std::ostream& operator<<( std::ostream& o, const AForm& frm );
