#include <iostream>
#include "FQueue.h"

FQueue::FQueue()
    : m_pHead(nullptr), m_pTail(nullptr) {};

FQueue::~FQueue(){
    FQClear();
}

bool FQueue::FQEmpty(){
    return (m_pHead) ? false : true;    //true = empty, false = not empty
}

int FQueue::FQEnqueue(FQINFO *ptr){
    FifoItem *newItem = new(std::nothrow) FifoItem(ptr);
    if(newItem == nullptr)
        throw FifoException(FIFO_ALLOCATION);

    if(FQEmpty())   //if empty
        m_pHead = m_pTail = newItem;
    else{
        m_pTail->m_pNext = newItem;
        m_pTail = newItem;
    }
    return 1;
}

FQINFO* FQueue::FQDequeue(){    //return info of deleted item
    if(FQEmpty())
        throw FifoException(FIFO_EMPTY);

    FQINFO* ptr = new FQINFO(m_pHead->m_pItem->nKey);
    ptr->p[0] = m_pHead->m_pItem->p[0];
    ptr->p[1] = m_pHead->m_pItem->p[1];
    FQDel();

    return ptr;
}

void FQueue::FQClear(){
    while(!FQEmpty()){
        FQDel();
    }
    m_pHead = nullptr;
    m_pTail = nullptr;
}

void FQueue::FQDel(){   //m_pItem zwalania sie orzy pomocy wlasnego destruktora
    if (!FQEmpty()){
        FifoItem* temp = m_pHead->m_pNext;
        delete m_pHead;
        m_pHead = temp;
    }
}