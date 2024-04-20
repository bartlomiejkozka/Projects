#include "Pupil.h"

/*int*/size_t Pupil::m_BaseID = 10000;

Pupil::Pupil(const std::string &pName, int pAge, const std::string &className) noexcept
    : Person(pName, pAge)
{
    setClassName(className);
    m_ID = std::to_string(m_BaseID);
    m_BaseID++;
    clearNotes();
    //for(int i = POLSKI; i < MAXSUBJECTS; i++)
        //m_Notes[i] = 0.0;
}

void Pupil::setNote(Subjects subject, double note){
    if(note >= 2 && note <= 5) {    // if(subject >= POLSKI && subject <= NIEMIECKI) - warunek ten jest nie potrzbeny
        m_Notes[subject] = note;    // gdyz gdy w razie podania blednego przemiotu (nie znajdujacego sie w enumie,
    }                               // kompilator sam pokaze blad
    else
        std::cerr << "Invalid subject or note!\n";
}

double Pupil::calcAve(){
    double sum = 0;
    int count = 0;
    for(int i = POLSKI; i < MAXSUBJECTS; i++){
        if (m_Notes[i] != 0.0) {
            sum += m_Notes[i];
            count++;
        }
    }
    return m_Ave = (count ? sum/count : 0); //jesli nie ma ocen to m_Ave = 0
}

void Pupil::printPupil(){
    std::cout << getID() << ", " << getName() << ", (" << getClassName()
                << "), " << getAge() << ", " << calcAve() << std::endl;
    std::cout << "\t";
    printOutfit();
}
