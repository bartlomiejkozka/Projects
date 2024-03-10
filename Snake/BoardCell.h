#ifndef SNAKEG_BOARDCELL_H
#define SNAKEG_BOARDCELL_H

#include "Board.h"
class Board;

enum CellType { EMPTY, SNAKE, APPLE };

class BoardCell {
private:
    CellType type;

public:
    BoardCell(CellType type) : type{type} {}
    virtual ~BoardCell() {}

    CellType getCellType() const {return this->type; }

    virtual int active(Board *ptr) = 0;
    virtual void create(Board *ptr) {};  //e.g. when create a new apple
    virtual void destroy(Board *ptr) {}; //e.g. when destroy an eaten apple
};

#endif
