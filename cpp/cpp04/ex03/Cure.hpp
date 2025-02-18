#include "ICharacter.hpp"

class Cure : public AMateria
{

public:
    //Constructors
    Cure();
    Cure( const Cure& other );

    //Destructors
    ~Cure();

    //Overloaded operators
    Cure& operator=( const Cure& other );

    //Other methods
    Cure* clone() const;
    void use(ICharacter& target);

};