#pragma once
#include <iostream>
#include "Pupil.h"

class SchoolBoy: public Pupil{
public:
    SchoolBoy(const std::string &boylName, int boyAge, const std::string &className) noexcept;

    virtual void printOutfit() final; //final - nie mozna jej nadpisac w klasie pochodnej
};
