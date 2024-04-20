#pragma once
#include <iostream>
#include <string>

class Person {
public:
    Person(const std::string &sName="", int newAge=0) noexcept; //nie moze rzucac wyjatkami
    virtual ~Person(); //new

    Person& operator = (const Person &p) = default; //nie mozna go implementowac

    void setName(const std::string &newName);
    void setAge(int newAge);
    void setPerson(const std::string &sNamem, int newAge);

    const std::string& getName() const;
    int getAge() const;

private:
    std::string m_Name;
    int m_Age;
};


//==========INLINE FUNCTION============
inline void Person::setName(const std::string &newName){
    m_Name = newName;
}
inline void Person::setAge(int newAge){
    m_Age = newAge;
}
inline void Person::setPerson(const std::string &sNamem, int newAge){
    setName(sNamem);
    setAge(newAge);
}

inline const std::string& Person::getName() const{
    return m_Name;
}
inline int Person::getAge() const{
    return m_Age;
}