#ifndef SNAKEG_EMPTYCELL_H
#define SNAKEG_EMPTYCELL_H

#include "BoardCell.h"

class EmptyCell : public BoardCell {
public:
    EmptyCell() : BoardCell(EMPTY) {}
    ~EmptyCell() {}

    int active(Board *ptr) override;
};

#endif
