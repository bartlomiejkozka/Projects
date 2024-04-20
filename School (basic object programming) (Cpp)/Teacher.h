#pragma once
#include "Worker.h"
#include "Pupil.h"

class Teacher: public Worker {
public:
    Teacher(const std::string &tName, int tAge, double salaryGross, int sYears, Subjects sub, bool isEdu,
            const std::string &tClass) noexcept;

    //konstruktor w wypadku gdy dany nauczyciel nie byl by wychowaca
    Teacher(const std::string &tName, int tAge, double salaryGross, int sYears, Subjects sub, bool isEdu) noexcept;

    void setSub(Subjects newSub);
    Subjects getSub() const;
    void setClass(const std::string &newClass);

    //void printTeacher();
    virtual void printInfo();
    void printSub();

    virtual double calcTax() final;
    virtual double calcSalaryNet() final;

private:
    Subjects m_subject;
    bool m_Is_Educator;
    std::string m_Class;
};

//==============INLINE FUNCTION===============
inline void Teacher::setSub(Subjects newSub){
    m_subject = newSub;
}

inline void Teacher::setClass(const std::string &newClass){
    if(m_Is_Educator){
        m_Class = newClass;
    }
}

inline Subjects Teacher::getSub() const{
    return m_subject;
}

inline double Teacher::calcSalaryNet(){
    return m_SalaryGross - calcTax();
}