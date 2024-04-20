#pragma once
#include "Pupil.h"

class SchoolGirl: public Pupil{
public:
    SchoolGirl(const std::string &girlName, int girlAge, const std::string &className) noexcept;

    void printOutfit() override; //override - kompiltor sprawdza czy istnieje taka funkcja w klasie bazowej
};

