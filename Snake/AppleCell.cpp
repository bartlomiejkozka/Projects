#include "AppleCell.h"
#include "SnakeCell.h"

int AppleCell::active(Board *ptr)
{
    ptr->getCell(ptr->getSnakeHeadPos())->destroy(ptr);     // create new apple in another place
    if(!ptr->replaceGridElement(ptr->getSnakeHeadPos(), new SnakeCell(ptr->getSnakePrevHead())))
        return 1;
    ptr->getCell(ptr->getSnakeHeadPos())->create(ptr);

    return 0;
}

void AppleCell::destroy(Board *ptr)
{
    srand(time(NULL));
    int digit = rand() % (ptr->getWidth()*ptr->getHeight());
    while(ptr->getCell(digit)->getCellType() == SNAKE || ptr->getCell(digit)->getCellType() == APPLE)
        digit = rand() % (ptr->getWidth()*ptr->getHeight());
    ptr->replaceGridElement(digit, new AppleCell());
}