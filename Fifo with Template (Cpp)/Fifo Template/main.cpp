#include <iostream>
#include "FQueue.h"

#define MAXITEM 5

int main() {

    FQueue<int> myQueue;    // kolejka intow

    try{
        for(int i = 0; i < MAXITEM; i++)
            myQueue.FQEnqueue(i);
    }
    catch(FifoException &e){
        std::cout << "Error: " << e.getReason() << std::endl;
    }

    try{
        std::cout << "The Queue of integers: " << std::endl;
        for(int i = 0; i < MAXITEM; i++) {
            int currItem = myQueue.FQDequeue();
            std::cout << currItem << std::endl;
        }
    }
    catch(FifoException &e){
        std::cout << "Error: " << e.getReason() << std::endl;
    }


    std::cout << std::endl;
    FQueue<char> myQueue1;  // kolejka charow

    try {
        for(char c = 'a'; c <= 'e'; c++)
            myQueue1.FQEnqueue(c);
    }
    catch(FifoException &e){
        std::cout << "Error: " << e.getReason() << std::endl;
    }

    try{
        std::cout << "The Queue of characters: " << std::endl;
        for(int i = 0; i < MAXITEM; i++) {
            char currItem = myQueue1.FQDequeue();
            std::cout << currItem << std::endl;
        }
    }
    catch(FifoException &e){
        std::cout << "Error: " << e.getReason() << std::endl;
    }

    std::cout << "Check is the queue is empty after using the FQDequeue function on all queue elements: " << std::endl;
    if(myQueue.FQEmpty()) std::cout << "The queue is empty\n";
    else std::cout << "The queue is not empty\n";


    std::cout << std::endl;
    // kolejka z elementami wskaznikow na int
    FQueue<int*> myQueue2;
    myQueue2.FQEnqueue(new (std::nothrow) int{1});
    myQueue2.FQEnqueue(new (std::nothrow) int{3});
    myQueue2.FQEnqueue(new (std::nothrow) int{9});
    myQueue2.FQEnqueue(new (std::nothrow) int{12});
    myQueue2.FQEnqueue(new (std::nothrow) int{16});

    std::cout << "The Queue of pointers to integers: " << std::endl;
    while( !myQueue2.FQEmpty() ){
        int *tmp = myQueue2.FQDequeue();
        std::cout << *tmp << std::endl;
        delete tmp;
    }

    return 0;
}
