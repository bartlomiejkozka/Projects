#pragma once
#include "Person.h"

class Worker: public Person {
public:
    Worker(const std::string &wName, int wAge, double salaryGross, int sYears) noexcept;

    void setSalary(double newSalary);
    void setYears(int sYears);
    void setWorker(double newSalary, int sYears);

    void printWorker();
    virtual void printInfo() = 0;

    virtual double calcTax() = 0;
    virtual double calcSalaryNet() = 0; //netto

protected:
    double m_SalaryGross;    //brutto
    static double m_yieldAmount; //kwota uzysku
    static double m_freeAmount; //kwota wolna
    int m_Years;

//private:

};


//============INLINE FUNCTION============
inline void Worker::setSalary(double newSalary){
    m_SalaryGross = newSalary;
}

inline void Worker::setYears(int sYears){
    m_Years = sYears;
}

inline void Worker::setWorker(double newSalary, int sYears){
    setSalary(newSalary);
    setYears(sYears);
}

inline void Worker::Worker::printWorker(){
    std::cout << getName() << ", ";
    printInfo();
}

