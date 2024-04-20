#pragma once
#include <iostream>
#include "Person.h"

enum Subjects{
    POLSKI,
    MATEMATYKA,
    FIZYKA,
    CHEMIA,
    INFORMATYKA,
    ANGIELSKI,
    NIEMIECKI,
    MAXSUBJECTS
};

class Pupil: public Person {
public:
    Pupil(const std::string &pName, int pAge, const std::string &className) noexcept; //new

    void setClassName(const std::string &NewClassName);
    const std::string& getClassName() const;

    const std::string& getID() const;

    void setNote(Subjects subject, double note);
    void clearNotes();

    double getAve() const;
    double calcAve();

    virtual void printOutfit() = 0; //klasa jest abstrkcyjna
    void printPupil();

protected:
    std::string m_ID;

private:
    static /*int*/ size_t m_BaseID; //aby wartosc nie mogla byc nigdy ujemna (moze tez byc usigned int)
    double m_Ave;
    std::string m_ClassName;
    double m_Notes[MAXSUBJECTS];
};


//==========INLINE FUNCTIONS============
inline void Pupil::setClassName(const std::string &NewClassName){
    m_ClassName = NewClassName;
}
inline const std::string& Pupil::getClassName() const{
    return m_ClassName;
}

inline const std::string& Pupil::getID() const{
    return m_ID;
}

inline void Pupil::clearNotes(){
    for(int i = POLSKI; i < MAXSUBJECTS; i++)
        m_Notes[i] = 0.0;
    //memset(m_Notes, 0, sizeof(m_Notes));
}

inline double Pupil::getAve() const{
    return m_Ave;
}

