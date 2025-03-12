#include "Serializer.hpp"
#include "Data.hpp"

int main()
{
    Data myData = {42, "fortytwo"};
    uintptr_t serializedPtr = Serializer::serialize(&myData);
    std::cout << "serialized the ptr to myData: " << serializedPtr << std::endl;
    Data* deserializedPtr = Serializer::deserialize(serializedPtr);
    std::cout << "deserializedPtr->myInt: " << deserializedPtr->myInt << std::endl;
    std::cout << "deserializedPtr->myString: " << deserializedPtr->myString << std::endl;
}