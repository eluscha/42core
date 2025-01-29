
#include <iostream>

enum e_level 
{
    INVALID,
    DEBUG, 
    INFO, 
    WARNING,
    ERROR
};

class Harl
{
    void debug( void );
    void info( void );
    void warning( void );
    void error( void );

public:

    Harl();
    ~Harl();

    void complain( std::string level );
};

enum e_level get_index( std::string level );