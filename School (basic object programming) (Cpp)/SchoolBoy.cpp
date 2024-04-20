#include "SchoolBoy.h"

SchoolBoy::SchoolBoy(const std::string &boyName, int boyAge, const std::string &className) noexcept
        : Pupil(boyName, boyAge, className)
{
    m_ID = "M_" + m_ID;
}

void SchoolBoy::printOutfit(){
    std::cout << "biala/niebieska koszula z krawatem, szkolna marynarka, polbuty, granatowa/czarna spodnie\n";
}