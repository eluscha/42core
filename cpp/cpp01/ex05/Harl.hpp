
#include <iostream>

#define HASHTSIZE 10

class Harl
{
    void debug( void );
    void info( void );
    void warning( void );
    void error( void );
    void invalid( void );

    typedef struct s_level 
    {
        std::string name;
        std::string to_check;
        void (Harl::*funcptr)();
    }   t_level;

    t_level hashTable[HASHTSIZE];

public:

    Harl();
    ~Harl();

    void complain( std::string level );

};