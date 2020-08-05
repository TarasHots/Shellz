#ifndef SHELLZ_FIELD_H
#define SHELLZ_FIELD_H

#include "definitions.h"
#include "Command.h"

namespace Battleships
{
    struct Field {
    public:
        bool placeShip(std::string_view placement);
        void display();

    private:
        const short columns = 10;
        const short rows = 10;

        std::vector<CellType> playerOwnField = std::vector<CellType>(columns * rows);
        std::vector<CellType> playerShootingField = std::vector<CellType>(columns * rows);

        [[nodiscard]] size_t calculate_coord(size_t x, size_t y) const {
            return columns * --y + --x;
        }

        bool isShipNearby(size_t x, size_t y, size_t ignore_x, size_t ignore_y);

        //TODO create Boat class, to encapsulate hits checks and nicely store somewhere
        bool place(Coordinates coordinates, const size_t &ship, const char &orientation);
    };
}

#endif //SHELLZ_FIELD_H
