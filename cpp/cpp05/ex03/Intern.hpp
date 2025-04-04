#pragma once

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
private:
    static std::string formnames[3];

public:
    //Constructors
    Intern();
    Intern( const Intern& other );

    //Destructors
    ~Intern();

    //Overloaded operators
    Intern& operator=( const Intern& other );

    //Public Methods

    AForm* makeForm( std::string name, std::string target) const;

};
