#pragma once
#include <iostream>

#define FIFO_ALLOCATION 0x01
#define FIFO_EMPTY 0x04
#define OTHER_ERROR 0x10

class FifoException{
public:
    FifoException(int errCode = OTHER_ERROR);
    const char* getReason() const;

private:
    int errCode;
};

//============FUNCTIONS IMPLEMENTATIONS FifoException===============
FifoException::FifoException(int errCode) : errCode(errCode) {}

const char* FifoException::getReason() const{
    switch(errCode){
        case FIFO_ALLOCATION:
            return "Fifo Allocation error";
        case FIFO_EMPTY:
            return "Fifo Empty error";
        case OTHER_ERROR:
            return "Fifo Other error";
        default:
            return "Unknown error";
    }
}

template<class T>
class FQueue;

template<class T>
class FifoItem{     //gdy nie piszemy public ani private to klasa automatyczne jest private
    friend class FQueue<T>;

    FifoItem(const T &item) : m_Item{item}, m_pNext{nullptr} {};

    T m_Item;
    FifoItem *m_pNext;
};

template<class T>
class FQueue{
public:
    FQueue();
    ~FQueue();

    bool FQEmpty();
    int FQEnqueue(const T &item);
    T FQDequeue();
    void FQClear();

private:
    FifoItem<T> *m_pHead;
    FifoItem<T> *m_pTail;
    void FQDel();
};

//============FUNCTIONS IMPLEMENTATIONS FQueue====================
template<class T>
FQueue<T>::FQueue() : m_pHead(nullptr), m_pTail(nullptr) {};

template<class T>
FQueue<T>::~FQueue(){ FQClear(); }

template<class T>
bool FQueue<T>::FQEmpty(){ return m_pHead == nullptr; }

template<class T>
int FQueue<T>::FQEnqueue(const T &item){
    FifoItem<T> *newItem = new(std::nothrow) FifoItem<T>(item);
    if(newItem == nullptr)
        throw FifoException(FIFO_ALLOCATION);

    if(FQEmpty())   // if empty
        m_pHead = m_pTail = newItem;
    else{
        m_pTail->m_pNext = newItem;
        m_pTail = newItem;
    }
    return 1;
}

template<class T>
T FQueue<T>::FQDequeue(){    // return deleted item
    if( FQEmpty() )
        throw FifoException(FIFO_EMPTY);

    T tmp = m_pHead->m_Item;
    FQDel();
    return tmp;
}

template<class T>
void FQueue<T>::FQClear(){
    while( !FQEmpty() ){
        FQDel();
    }
    m_pHead = nullptr;
    m_pTail = nullptr;
}

template<class T>
void FQueue<T>::FQDel() {
    if( !FQEmpty() ){
        FifoItem<T> *tmp = m_pHead->m_pNext;
        delete m_pHead;
        m_pHead = tmp;
    }
}



