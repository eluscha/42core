#include "Ice.hpp"

//Constructors
Ice::Ice() : AMateria("ice")
{
   //std::cout << "Ice default constructor is called" << std::endl;
}

Ice::Ice( const Ice& other ) : AMateria(other)
{
   //std::cout << "Ice copy constructor is called" << std::endl;
}

//Destructors
Ice::~Ice()
{
   //std::cout << "Ice destructor is called" << std::endl;
}

//Overloaded operators
Ice& Ice::operator=( const Ice& other )
{
   //std::cout << "Ice =operator is called" << std::endl;
   if (this == &other)
      return (*this);
   //here one would copy attributes if there were any, but _type is there already
   return (*this);
}

//Other methods
Ice* Ice::clone() const
{
   return (new Ice(*this));
}

void Ice::use(ICharacter& target)
{
   std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
