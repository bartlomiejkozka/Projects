#include <iostream>
#include "Person.h"
#include "Pupil.h"
#include "SchoolGirl.h"
#include "SchoolBoy.h"
#include "Worker.h"
#include "Teacher.h"
#include "Admin.h"

#ifndef MAXPUPIL
    #define MAXPUPIL 9
#endif

#ifndef MAXWORKER
    #define MAXWORKER 9
#endif

void printPupils(Pupil** tab, int PupilNo);
void printWorkers(Worker** tab, int WorkerNo);
void sortPupils(Pupil** tab, int PupilNo);

int main() {

    Pupil* pupils[MAXPUPIL] = {nullptr};
    Pupil* v = nullptr;

    pupils[0] = v = new SchoolGirl("Mot Agnieszka", 17, "3b");
    v->setNote(POLSKI, 3);
    v->setNote(MATEMATYKA, 4.5);
    v->setNote(FIZYKA, 4);
    v->setNote(CHEMIA, 4);
    v->setNote(INFORMATYKA, 5);
    v->setNote(ANGIELSKI, 4.5);
    v->setNote(NIEMIECKI, 3.5);

    pupils[1] = v = new SchoolGirl("Bob Ada", 18, "4b");
    //v->setNote(POLSKI, 3);
    v->setNote(MATEMATYKA, 3.5);
    v->setNote(FIZYKA, 3);
    //v->setNote(CHEMIA, 4);
    v->setNote(INFORMATYKA, 3.5);
    v->setNote(ANGIELSKI, 4);
    //v->setNote(NIEMIECKI, 3.5);

    pupils[2] = v = new SchoolGirl("Fenk Zofia", 18, "4c");
    v->setNote(POLSKI, 3);
    v->setNote(MATEMATYKA, 4.5);
    //v->setNote(FIZYKA, 3);
    v->setNote(CHEMIA, 3.5);
    //v->setNote(INFORMATYKA, 3.5);
    //v->setNote(ANGIELSKI, 4);
    v->setNote(NIEMIECKI, 4);

    pupils[3] = v = new SchoolGirl("Zloto Emilia", 16, "2a");
    v->setNote(POLSKI, 4);
    v->setNote(MATEMATYKA, 3.5);
    //v->setNote(FIZYKA, 3);
    //v->setNote(CHEMIA, 4);
    //v->setNote(INFORMATYKA, 3.5);
    //v->setNote(ANGIELSKI, 4);
    v->setNote(NIEMIECKI, 3.5);

    pupils[4] = v = new SchoolGirl("Nowaczkiewicz Teresa", 17, "3d");
    v->setNote(POLSKI, 3);
    v->setNote(MATEMATYKA, 3.5);
    //v->setNote(FIZYKA, 3);
    //v->setNote(CHEMIA, 4);
    //v->setNote(INFORMATYKA, 3.5);
    //v->setNote(ANGIELSKI, 4);
    v->setNote(NIEMIECKI, 3.5);

    pupils[5] = v = new SchoolGirl("Pop Elzbieta", 15, "1c");
    v->setNote(POLSKI, 4);
    v->setNote(MATEMATYKA, 5);
    v->setNote(FIZYKA, 5);
    v->setNote(CHEMIA, 4);
    v->setNote(INFORMATYKA, 4.5);
    //v->setNote(ANGIELSKI, 4);
    v->setNote(NIEMIECKI, 4);

    pupils[6] = v = new SchoolBoy("Code Bro", 18, "4b");
    v->setNote(POLSKI, 3);
    v->setNote(MATEMATYKA, 4.5);
    v->setNote(FIZYKA, 3.5);
    v->setNote(CHEMIA, 3);
    v->setNote(INFORMATYKA, 4.5);
    v->setNote(ANGIELSKI, 4);
    //v->setNote(NIEMIECKI, 3.5);

    pupils[7] = v = new SchoolBoy("Koz Bart", 18, "4b");
    v->setNote(POLSKI, 3);
    //v->setNote(MATEMATYKA, 3.5);
    v->setNote(FIZYKA, 4);
    v->setNote(CHEMIA, 2);
    v->setNote(INFORMATYKA, 3.5);
    v->setNote(ANGIELSKI, 4);
    //v->setNote(NIEMIECKI, 3.5);

    pupils[8] = v = new SchoolBoy("Benk Maciej", 17, "3b");

    sortPupils( pupils, MAXPUPIL);
    printPupils(pupils, MAXPUPIL);


    //-----------------------------------------------

    Worker* workers[MAXWORKER] = {nullptr};

    workers[0] = new Teacher("Nowak Anna", 30, 3000.00, 1, NIEMIECKI, false);
    workers[1] = new Teacher("Szymanska Eliza", 40, 3800.00, 10, POLSKI, true, "3c");
    workers[2] = new Teacher("Szeks Aleksandra", 37, 3500.00, 5, ANGIELSKI, false);
    workers[3] = new Teacher("Wisnia Piotr", 45, 4400.00, 16, INFORMATYKA, true, "4b");
    workers[4] = new Teacher("Trapez Jadwiga", 43, 4100.00, 12, MATEMATYKA, true, "3b");
    workers[5] = new Teacher("Sopel Kamil", 33, 3600.00, 6, FIZYKA, false);

    workers[6] = new Admin("Blackwood Zephyr", 50, 10000.00, 25, STARSZY_SPECJALISTA);
    workers[7] = new Admin("Głowacki Borys", 39, 7000.00, 10, SPECJALISTA);
    workers[8] = new Admin("Łukasik Leonard", 27, 5000.00, 2, MLODSZY_SPECJALISTA);

    printWorkers(workers, MAXWORKER);

    return 0;
}



//============FUNCTIONS====================
void printPupils(Pupil** tab, int PupilNo){
    for(int i = 0; i < PupilNo; i++){
        tab[i]->printPupil();
        std::cout << "\n\n";
    }
}

void printWorkers(Worker** tab, int WorkerNo){
    for(int i = 0; i < WorkerNo; i++){
        tab[i]->printWorker();
        std::cout << "\n";
    }
}

void sortPupils(Pupil** tab, int PupilNo){
    for(int i = 1; i < PupilNo; i++){
        int j = i - 1;
        Pupil* v = tab[i];
        while(j>=0 && v->getName() < tab[j]->getName()) {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j+1] = v;
    }
}

