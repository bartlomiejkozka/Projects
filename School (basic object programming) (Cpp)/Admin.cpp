#include "Admin.h"

Admin::Admin(const std::string &aName, int aAge, double salaryGross, int sYears, Worksite pos) noexcept
                : Worker(aName, aAge, salaryGross, sYears)
{
    setPosition(pos);
}

void Admin::printInfo(){
    printPosition();
    std::cout << ", "<< "Brutto: " << m_SalaryGross << ", Podatek: " << calcTax()
              << ", Netto: " << calcSalaryNet() << std::endl;;
}

void Admin::printPosition(){
    switch(getPosition()){
        case MLODSZY_SPECJALISTA:
            std::cout << "Mlodzy Specjalista";
            break;
        case SPECJALISTA:
            std::cout << "Specjalista";
            break;
        case STARSZY_SPECJALISTA:
            std::cout << "Starszy Specjalista";
            break;
    }
}