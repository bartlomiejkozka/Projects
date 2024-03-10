#ifndef SNAKEG_BOARD_H
#define SNAKEG_BOARD_H

#include <cstdlib>
#include <ctime>

class BoardCell;
class EmptyCell;
class SnakeCell;
class AppleCell;

enum orientation { UP, DOWN, RIGHT, LEFT };

class Board {
private:
    BoardCell **grid;
    int width;
    int height;
    int headPos;    //Snake head
    orientation orient;    //Snake orientation
    //orientation prevOrient;

public:
    SnakeCell *head = nullptr;
    SnakeCell *prevHead = nullptr;

public:
    Board(int newWidth, int newHeight);
    ~Board();

    void changeSnakeDirection();
    bool isOffGrid();
    bool advance();
    bool replaceGridElement(int x, BoardCell *cell);
    int getPosition(BoardCell *cell);
    void createFirstApple();

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    BoardCell* getCell(int pos) { return grid[pos]; }
    int getSnakeHeadPos() const { return this->headPos; }
    SnakeCell* getSnakePrevHead() const { return prevHead; }
    void setCell(int x, BoardCell *cell) { this->grid[x] = cell; }


    void setOrientation(orientation o) {
        if (!isOppositeDirection(o, orient)) {
            orient = o;
        }
    }
    bool isOppositeDirection(orientation o, orientation current) {
        return ((o == DOWN && current == UP) ||
                (o == UP && current == DOWN) ||
                (o == LEFT && current == RIGHT) ||
                (o == RIGHT && current == LEFT));
    }
};

#endif
