#include "EmptyCell.h"
#include "SnakeCell.h"

int EmptyCell::active(Board *ptr)
{
    if(!ptr->replaceGridElement(ptr->getSnakeHeadPos(), new SnakeCell(ptr->getSnakePrevHead())))   //if the replacement will not succeed
        return 1;
    ptr->getCell(ptr->getSnakeHeadPos())->create(ptr);      // update Snake head
    ptr->getCell(ptr->getSnakeHeadPos())->destroy(ptr);     // destroy last Snake el.

    return 0;
}
