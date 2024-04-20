#pragma once
#include "Worker.h"

enum Worksite{
    MLODSZY_SPECJALISTA,
    SPECJALISTA,
    STARSZY_SPECJALISTA
};

class Admin: public Worker {
public:
    Admin(const std::string &aName, int aAge, double salaryGross, int sYears, Worksite pos) noexcept;

    void setPosition(Worksite newPosition);
    Worksite getPosition() const;

    //void printAdmin();
    virtual void printInfo();
    void printPosition();

    virtual double calcTax() final;
    virtual double calcSalaryNet() final;

private:
    Worksite m_Position;
};

//==========INLINE FUNCTION=============
inline void Admin::setPosition(Worksite newPosition){
    /*if(NewPosition >= 0 && NewPosition <= 2)
        m_Position = NewPosition;
    else
        std::cerr << "Invalid Worksite!\n";*/
    m_Position = newPosition;
}

inline Worksite Admin::getPosition() const{
    return m_Position;
}

inline double Admin::calcTax(){
    double tax = (m_SalaryGross - m_yieldAmount) * 0.18 - m_freeAmount;
    if(tax > 0)
        return tax;
    else return 0;
}

inline double Admin::calcSalaryNet(){
    return m_SalaryGross - calcTax();
}