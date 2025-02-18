#include "ICharacter.hpp"

class Ice : public AMateria
{

public:
    //Constructors
    Ice();
    Ice( const Ice& other );

    //Destructors
    ~Ice();

    //Overloaded operators
    Ice& operator=( const Ice& other );

    //Other methods
    Ice* clone() const;
    void use(ICharacter& target);

};