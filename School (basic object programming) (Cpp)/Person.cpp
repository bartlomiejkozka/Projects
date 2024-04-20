#include "Person.h"

Person::Person(const std::string &sName, int newAge) noexcept{
    setPerson(sName, newAge);
}

Person::~Person(){}

