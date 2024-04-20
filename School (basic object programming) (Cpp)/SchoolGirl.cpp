#include "SchoolGirl.h"

SchoolGirl::SchoolGirl(const std::string &girlName, int girlAge, const std::string &className) noexcept
    : Pupil(girlName, girlAge, className)
{
    m_ID = "F_" + m_ID;
}

void SchoolGirl::printOutfit(){
    std::cout << "biala bluzka z krawatem, szkolna marynarka, granatowa/czarna spodniczka, plaskie obuwie\n";
}