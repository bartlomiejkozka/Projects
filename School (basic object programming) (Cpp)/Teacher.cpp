#include "Teacher.h"

Teacher::Teacher(const std::string &tName, int tAge, double salaryGross, int sYears, Subjects sub, bool isEdu,
                 const std::string &tClass) noexcept
                    : Worker(tName, tAge, salaryGross, sYears)
{
    setSub(sub);
    m_Is_Educator = isEdu;
    setClass(tClass);
}

Teacher::Teacher(const std::string &tName, int tAge, double salaryGross, int sYears, Subjects sub, bool isEdu) noexcept
                    : Worker(tName, tAge, salaryGross, sYears)
{
    setSub(sub);
    m_Is_Educator = isEdu;
}

double Teacher::calcTax(){
    double salaryGross = m_SalaryGross;
    if(m_Is_Educator)
        salaryGross += 400;

    if(m_Years >= 5 && m_Years <= 20){
        salaryGross += salaryGross * (static_cast<double>(m_Years)/100);
    }else if(m_Years > 20){
        salaryGross += salaryGross * 0.2;
    }

    double tax = ((0.8 * salaryGross - 0.5 * m_yieldAmount)
                + (0.2 * salaryGross - m_yieldAmount)) * 0.18 - m_freeAmount;
    if(tax > 0)
        return tax;
    else return 0;
}

void Teacher::printInfo(){
    printSub();
    std::cout << ", " << "Brutto: " << m_SalaryGross << ", Podatek: " << calcTax()
              << ", Netto: " << calcSalaryNet() << std::endl;
}

void Teacher::printSub(){
    switch(getSub()){
        case POLSKI:
            std::cout << "Jezyk Polski";
            break;
        case MATEMATYKA:
            std::cout << "Matematyka";
            break;
        case FIZYKA:
            std::cout << "Fizyka";
            break;
        case CHEMIA:
            std::cout << "Chemia";
            break;
        case INFORMATYKA:
            std::cout << "Informatyka";
            break;
        case ANGIELSKI:
            std::cout << "Jezyk Angielski";
            break;
        case NIEMIECKI:
            std::cout << "Jezyk Niemiecki";
            break;
    }
}