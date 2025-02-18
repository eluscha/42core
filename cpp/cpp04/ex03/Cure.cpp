#include "Cure.hpp"

 //Constructors
 Cure::Cure() : AMateria("cure")
 {
    std::cout << "Cure default constructor is called" << std::endl;
 }

 Cure::Cure( const Cure& other ) : AMateria(other)
 {
    std::cout << "Cure copy constructor is called" << std::endl;
 }

 //Destructors
 Cure::~Cure()
 {
    std::cout << "Cure destructor is called" << std::endl;
 }

 //Overloaded operators
 Cure& Cure::operator=( const Cure& other )
 {
    if (this == &other)
        return (*this);
    _type = other._type;
    return (*this);
 }

 //Other methods
 Cure* Cure::clone() const
 {
    Cure* clone = new Cure(*this);
    return (clone);
 }

 void Cure::use(ICharacter& target)
 {
   std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
 }
 