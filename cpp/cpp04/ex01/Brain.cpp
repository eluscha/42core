#include "Brain.hpp"

//Constructors
Brain::Brain()
{
    std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain( const Brain& other )
{
    std::cout << "Brain copy constructor called" << std::endl;
    *this = other;
}

//Destructors
Brain::~Brain()
{
    std::cout << "Brain destructor called" << std::endl;
}

//Overloaded operators
Brain& Brain::operator=( const Brain& other )
{
    std::cout << "Brain operator= called" << std::endl;
    for (int i = 0; i < 100; i++)
        _ideas[i] = other._ideas[i];
    return (*this);
}

//Other methods
const std::string& Brain::getIdea( int num ) const
{
    if (num < 0 || num > 99)
    {
        std::cerr << "\nError: Brain obj.getIdea(): Invalid index for _ideas array." << std::endl;
        return (_ideas[99]);
    }
    return (_ideas[num]);
}

void Brain::setIdea( std::string idea, int num )
{
    if (num < 0 || num > 99)
    {
        std::cerr << "Error: Brain obj.getIdea(): Invalid index for _ideas array" << std::endl;
        return ;
    }
    _ideas[num] = idea;
}