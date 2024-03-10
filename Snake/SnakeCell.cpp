#include "SnakeCell.h"
#include "EmptyCell.h"

void SnakeCell::create(Board *ptr) { ptr->head = dynamic_cast<SnakeCell *>(ptr->getCell(ptr->getSnakeHeadPos())); }

int SnakeCell::active(Board *ptr)
{
    return 1;
}

void SnakeCell::destroy(Board *ptr)
{
    if(!ptr->head) return;

    SnakeCell *toRemove = ptr->head;
    SnakeCell *prev = nullptr;
    while(toRemove->next != nullptr) {
        prev = toRemove;
        toRemove = toRemove->next;
    }
    if(prev)
        prev->next = nullptr;
    ptr->replaceGridElement(ptr->getPosition(toRemove), new EmptyCell());
}
