#include "Intern.hpp"

//static attributes
std::string Intern::formnames[3] = {
    "Shrubbery Creation",
	"Robotomy Request",
	"Presidential Pardon"}; 

//Constructors
Intern::Intern() {}
Intern::Intern( const Intern& other )
{
    (void)other;
}

//Destructors
Intern::~Intern() {}

//Overloaded operators
Intern& Intern::operator=( const Intern& other )
{
    (void)other;
    return (*this);
}

//Public Methods
AForm* Intern::makeForm( std::string name, std::string target) const
{
    AForm* frm;
    int i = 0;
    while (i < 3 && name != formnames[i])
    {
        i++;
    }
    switch (i)
	{
		case 0:
			frm = new ShrubberyCreationForm(target);
			break;
		case 1:
			frm = new RobotomyRequestForm(target);
			break;
		case 2:
			frm = new PresidentialPardonForm(target);
			break;
		default:
            std::cerr << "\033[31mName \"" << name << "\" does not match any form\033[0m" << std::endl;
            return (NULL);;
	}
	std::cout << "Intern creates " << name << std::endl;
	return frm;
}