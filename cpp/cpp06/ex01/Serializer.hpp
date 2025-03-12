#pragma once

#include "Data.hpp"
#include <iostream>
#include <stdint.h>

class Serializer
{
private:
    //Constructors
    Serializer();
    Serializer( const Serializer& other );

    //Destructors
    ~Serializer();

    //Overloaded operators
    Serializer& operator=( const Serializer& other );

public:
    //Static public methods
    static uintptr_t serialize( Data* ptr );
    static Data* deserialize( uintptr_t raw );
};