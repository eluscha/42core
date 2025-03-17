#include <iostream>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base* generate( void );
void identify( Base* p );
void identify( Base& p );

int main()
{
    Base* APtr = new A();
    std::cout << "APtr type identified as: ";
    identify(APtr);
    A a;
    std::cout << "Reference to A object identified as: ";
    identify(a);


    Base* BPtr = new B();
    std::cout << "BPtr type identified as: ";
    identify(BPtr);
    if (BPtr != NULL)
    {
        std::cout << "Reference to B object identified as: ";
        identify(*BPtr);
    }

    Base* CPtr = new C();
    std::cout << "CPtr type identified as: ";
    identify(CPtr);
    C c;
    Base& CRef = c;
    std::cout << "Reference to C object identified as: ";
    identify(CRef);

    Base* Ptr = generate();
    std::cout << "Randomly generated Ptr type identified as: ";
    identify(Ptr);
    if (Ptr != NULL)
    {
        std::cout << "When passed as reference: ";
        identify(*Ptr);
    }

    delete APtr;
    delete BPtr;
    delete CPtr;
    delete Ptr;
}