#ifndef SNAKEG_SNAKECELL_H
#define SNAKEG_SNAKECELL_H

#include "BoardCell.h"

class SnakeCell : public BoardCell {
public:
    SnakeCell *next;

public:
    SnakeCell(SnakeCell *prevHead) : BoardCell(SNAKE), next{prevHead} {}
    ~SnakeCell() {}

    int active(Board *ptr) override;
    void create(Board *ptr) override;
    void destroy(Board *ptr) override;   // delete last Snake el.

};

#endif
