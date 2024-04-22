#include <iostream>
#include "FQueue.h"
#include "global.h"

#define MAXINFO 5
#define FQINFO FQInfo

int main() {
    FQueue myQueue;

    FQINFO *info1 = new FQINFO(1);
    info1->p[0] = 10;
    info1->p[1] = 11;
    FQINFO *info2 = new FQINFO(2);
    info2->p[0] = 20;
    info2->p[1] = 21;
    FQINFO *info3 = new FQINFO(3);
    info3->p[0] = 30;
    info3->p[1] = 31;
    FQINFO *info4 = new FQINFO(4);
    info4->p[0] = 40;
    info4->p[1] = 41;
    FQINFO *info5 = new FQINFO(5);
    info5->p[0] = 50;
    info5->p[1] = 51;

    try{
        myQueue.FQEnqueue(info1);
        myQueue.FQEnqueue(info2);
        myQueue.FQEnqueue(info3);
        myQueue.FQEnqueue(info4);
        myQueue.FQEnqueue(info5);
    }
    catch(FifoException &e){
        std::cout << "Error: " << e.getReason() << std::endl;
    }

    for(int i = 0; i < MAXINFO; i++){
        try{
            FQINFO *currentinfo = myQueue.FQDequeue();
            std::cout << *currentinfo << std::endl;
        }
        catch(FifoException &e){
            std::cout << "Error: " << e.getReason() << std::endl;
        }
    }

    if(myQueue.FQEmpty()) std::cout << "The queue is empty\n";
    else std::cout << "The queue is not empty\n";

    return 0;
}
