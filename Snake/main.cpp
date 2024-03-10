#include <iostream>

#include "BoardCell.h"
#include "Render.h"

int main(int argc, char *argv[])
{
    Render *game = new Render(10,11);
    game->run();
    game->clean();
    delete game;

    return 0;
}
