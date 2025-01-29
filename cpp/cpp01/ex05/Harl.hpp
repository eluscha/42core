
#include <iostream>

class Harl
{
    void debug( void );
    void info( void );
    void warning( void );
    void error( void );

    typedef struct s_level {
        const char* name;
        void (Harl::*funcptr)();
    }   t_level;

    static t_level levelTable[];

public:

    Harl();
    ~Harl();

    void complain( std::string level );

};