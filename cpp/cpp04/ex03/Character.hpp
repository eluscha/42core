#include "ICharacter.hpp"

class Character : public ICharacter
{

    //Constructors
    Character();
    Character( const Character& other );

    public:

    //Destructors
    virtual ~Character();

    //Overloaded operators
    Character& operator=( const Character& other );

    //Other methods

};