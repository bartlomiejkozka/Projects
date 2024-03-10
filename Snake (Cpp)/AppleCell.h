#ifndef SNAKEG_APPLECELL_H
#define SNAKEG_APPLECELL_H

#include "Board.h"
#include "BoardCell.h"

class AppleCell : public BoardCell {
public:

    AppleCell() : BoardCell(APPLE) {}
    ~AppleCell() {}

    int active(Board *ptr) override;
    void create(Board *ptr) override {}
    void destroy(Board *ptr) override;      //gdy usuwane jest jablko pojawia sie nowe w innym miejsc
};

#endif