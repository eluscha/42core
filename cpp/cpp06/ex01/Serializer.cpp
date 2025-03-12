#include "Serializer.hpp"

//Constructors
Serializer::Serializer() {}
Serializer::Serializer( const Serializer& other ) 
{
    (void)other;
}

//Destructors
Serializer::~Serializer() {}

//Overloaded operators
Serializer& Serializer::operator=( const Serializer& other )
{
    (void)other;
    return (*this);
}

//static methods
uintptr_t Serializer::serialize( Data* ptr )
{
    return (reinterpret_cast<uintptr_t>(ptr)); // Convert a pointer to a big enough integer
}

Data* Serializer::deserialize( uintptr_t raw )
{
    return (reinterpret_cast<Data*>(raw));
}
