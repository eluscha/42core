#pragma once

#include <iostream>

class Brain
{
    std::string _ideas[100];

public:
    //Constructors
    Brain();
    Brain( std::string type );
    Brain( const Brain& other );

    //Destructors
    ~Brain();

    //Overloaded operators
    Brain& operator=( const Brain& other );

    //Other methods
    const std::string& getIdea( int num ) const;
    void setIdea( std::string idea, int num );
};
