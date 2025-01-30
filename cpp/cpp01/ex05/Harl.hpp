
#include <iostream>

class Harl
{
    void debug( void );
    void info( void );
    void warning( void );
    void error( void );
    void nop( void );

    typedef struct s_level 
    {
        const char* name;
        void (Harl::*funcptr)();
    }   t_level;

    t_level levelTable[10];

public:

    Harl();
    ~Harl();

    void complain( std::string level );

};