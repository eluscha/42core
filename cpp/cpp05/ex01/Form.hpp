#pragma once

#include <iostream>

class Bureaucrat;

class Form
{
private:
    const std::string _name;
    bool  _issigned;
    const int _grade_sign;
    const int _grade_exec;

    //Private Constructors
    Form();

public:
    //Public Constructors
    Form( const std::string& name, int grade_sign, int grade_exec );
    Form( const Form& other );

    //Destructors
    ~Form();

    //Overloaded operators
    Form& operator=( const Form& other );

    //Getters
    std::string getName() const;
    bool getIsSigned() const;
    int getGradeSign() const;
    int getGradeExec() const;

    //Public Methods
    bool beSigned( const Bureaucrat& brcrt );

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

std::ostream& operator<<( std::ostream& o, const Form& frm );
