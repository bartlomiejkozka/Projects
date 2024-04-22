#pragma once
#include "global.h"

#define FIFO_ALLOCATION 0x01
#define FIFO_EMPTY 0x04
#define OTHER_ERROR 0x10

class FifoItem{
public:
    FifoItem(FQINFO *ptr=nullptr);
    virtual ~FifoItem();

    FQINFO *m_pItem;
    FifoItem *m_pNext;
};

class FQueue{
public:
    FQueue();
    virtual ~FQueue();

    bool FQEmpty();
    int FQEnqueue(FQINFO *ptr);
    FQINFO* FQDequeue();
    void FQClear();

private:
    FifoItem *m_pHead;
    FifoItem *m_pTail;
    void FQDel();
};

class FifoException{
public:
    FifoException(int errCode = OTHER_ERROR);
    const char* getReason() const;

private:
    int errCode;
};


//============INLINE FUNCTIONS FIFOITEM===============

inline FifoItem::FifoItem(FQINFO *ptr)
    : m_pItem(ptr), m_pNext(nullptr) {}

inline FifoItem::~FifoItem(){
    delete m_pItem;
}

//============INLINE FUNCTIONS FIFOEXCEPTION===============
inline FifoException::FifoException(int errCode) : errCode(errCode) {}

inline const char* FifoException::getReason() const{
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




