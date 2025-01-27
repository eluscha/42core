
#pragma once
#include <string>

class Weapon
{
    std::string _type;

public:

    Weapon();
    Weapon( std::string tp );
    ~Weapon();

    std::string getType( void );
    void setType( std::string tp);
    
};