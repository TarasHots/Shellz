#ifndef SHELLZ_DEFINITIONS_H
#define SHELLZ_DEFINITIONS_H

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <stdexcept>
#include <memory>
#include <sstream>


namespace Battleships
{
    enum CellType
    {
        EMPTY = 0,
        SHIP = 1,
        DAMAGED = 2,
        MISS = 3
    };

    struct Coordinates
    {
        short x, y;

        Coordinates(short x, short y)
        {
            this->x = x;
            this->y = y;
        }
    };
}

#endif //SHELLZ_DEFINITIONS_H
