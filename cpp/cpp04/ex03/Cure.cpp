#include "Cure.hpp"

//Constructors
Cure::Cure() : AMateria("cure")
{
   //std::cout << "Cure default constructor is called" << std::endl;
}

Cure::Cure( const Cure& other ) : AMateria(other)
{
   //std::cout << "Cure copy constructor is called" << std::endl;
}

//Destructors
Cure::~Cure()
{
   //std::cout << "Cure destructor is called" << std::endl;
}

//Overloaded operators
Cure& Cure::operator=( const Cure& other )
{
   //std::cout << "Cure =operator is called" << std::endl;
   if (this == &other)
      return (*this);
   //here one would copy attributes if there were any, but _type is there already
   return (*this);
}

//Other methods
Cure* Cure::clone() const
{
   return (new Cure(*this));
}

void Cure::use(ICharacter& target)
{
   std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}
