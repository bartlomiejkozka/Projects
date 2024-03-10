#include "Board.h"
#include "SnakeCell.h"
#include "EmptyCell.h"
#include "AppleCell.h"

Board::Board(int newWidth, int newHeight) : width{newWidth}, height{newHeight}
{
    grid = new BoardCell*[width*height];
    grid[0] = new SnakeCell(prevHead);
    for(int i=1; i<width * height; ++i)
        grid[i] = new EmptyCell();

    head = dynamic_cast<SnakeCell *>(grid[0]);
    this->headPos = 0;
    orient = DOWN;
    createFirstApple();
}

Board::~Board()
{
    for(int i=0; i<width * height; ++i)
        delete grid[i];
    delete[] grid;
}

void Board::changeSnakeDirection()
{
    switch(orient) {
        case DOWN:
            this->headPos += getWidth();
            break;
        case UP:
            this->headPos -= getWidth();
            break;
        case LEFT:
            this->headPos -= 1;
            break;
        case RIGHT:
            this->headPos += 1;
            break;
    }
}

bool Board::isOffGrid()
{
    int prevHeadPos = this->headPos;
    changeSnakeDirection();
    //1-st case - top band
    for(int i=0; i<getWidth(); ++i)
        if(prevHeadPos == i) if(orient == UP) return false;
    //2-nd case - left band
    for(int i=0; i<getHeight()*getWidth(); i+=getWidth())
        if(prevHeadPos == i) if(orient == LEFT) return false;
    //3-rd case - bottom band
    for(int i=(getHeight()*getWidth())-getWidth(); i<getHeight()*getWidth(); ++i)
        if(prevHeadPos == i) if(orient == DOWN) return false;
    //4-th case - right band
    for(int i=getWidth()-1; i<getHeight()*getWidth(); i+=getWidth())
        if(prevHeadPos == i) if(orient == RIGHT) return false;

    return true;
}

bool Board::advance()
{
    // trzeba zapamietac wskaznik na glowe weza zanim pozycja glowy weza zmieni sie, aby pozniej moc ustawic wsk.next
    // na poprzednia pozycje glowy weza albo nw czy nie lepszym pomyslem bedze stworzenie zmiennej klasowej SnaekCell *prevHead?
    prevHead = dynamic_cast<SnakeCell *>(getCell(getSnakeHeadPos()));
    if(!isOffGrid()) return false;

    if(getCell(this->headPos)->active(this))
        return false;

    return true;
}

bool Board::replaceGridElement(int x, BoardCell *cell)
{
    if(!cell) return false;
    if(this->grid[x] != nullptr)
        delete this->grid[x];

    setCell(x, cell);
    return true;
}

int Board::getPosition(BoardCell *cell)
{
    for(int i=0; i<getWidth()*getHeight(); ++i) {
        if(cell == grid[i]) return i;
    }
    return -1;
}

void Board::createFirstApple()
{
    srand(time(nullptr));
    int digit = rand() % (getWidth()*getHeight());
    while(digit == getSnakeHeadPos())
        digit = rand() % (getWidth()*getHeight());
    replaceGridElement(digit, new AppleCell());
}