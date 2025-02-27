#pragma once

#include <iostream>
#include <exception>

class Bureaucrat
{
    const std::string   _name;
    int                 _grade;

public:
    //Constructors
    Bureaucrat();
    Bureaucrat( int grade );
    Bureaucrat( const std::string& name, int grade );
    Bureaucrat( const Bureaucrat& other );

    //Destructors
    ~Bureaucrat();

    //Overloaded operators
    Bureaucrat& operator=( const Bureaucrat& other );

    //Getters
    std::string getName() const;
    int getGrade() const;

    //Public Methods
    void incrementGrade();
    void decrementGrade();

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

std::ostream& operator<<( std::ostream& o, const Bureaucrat& brcrt );
