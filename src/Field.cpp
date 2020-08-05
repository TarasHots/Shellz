//
// Created by Taras Hots on 05/08/2020.
//

#include "Field.h"

using namespace Battleships;

bool Field::placeShip(std::string_view placement)
{
    auto command = std::make_unique<Command>(placement);

    return place(command->get_coordinates(), command->get_ship(), command->get_orientation());
}

void Field::display()
{
    std::string_view letters_row{"  | A | B | C | D | E | F | G | H | I | J |"};
    std::string_view delimiter{"-------------------------------------------"};

    std::cout << letters_row << std::endl;

    short cells_count = 1, max = columns, row_counter = 1;

    std::cout << row_counter << " | ";

    for (auto cell : playerOwnField) {
        if (cells_count == max) {
            std::cout << cell << " | " << std::endl;

            cells_count = 1;

            if (row_counter < max) {
                row_counter++;
                std::cout << row_counter << (row_counter >= 10 ? "| " : " | ");
            }

            continue;
        };

        std::cout << cell << " | ";
        ++cells_count;
    }
}

bool Field::isShipNearby(size_t x, size_t y, size_t ignore_x, size_t ignore_y)
{
    size_t right_x = ++x;
    size_t left_x = --x;
    size_t up_y = --y;
    size_t down_y = ++y;

    if (playerOwnField.at(calculate_coord(++x, y)) != CellType::SHIP
        || playerOwnField.at(calculate_coord(--x, y)) != CellType::SHIP) {
        return true;
    }

    if (playerOwnField.at(calculate_coord(x, ++y)) != CellType::SHIP
        || playerOwnField.at(calculate_coord(x, --y)) != CellType::SHIP) {
        return true;
    }

    if (playerOwnField.at(calculate_coord(++x, ++y)) != CellType::SHIP
        || playerOwnField.at(calculate_coord(--x, --y)) != CellType::SHIP) {
        return true;
    }

    if (playerOwnField.at(calculate_coord(--x, ++y)) != CellType::SHIP
        || playerOwnField.at(calculate_coord(++x, --y)) != CellType::SHIP) {
        return true;
    }

    return false;
}

bool Field::place(const Coordinates coordinates, const size_t &ship, const char &orientation)
{
    try {
        auto first_cell = playerOwnField.at(calculate_coord(coordinates.x, coordinates.y));

        if (first_cell != EMPTY) throw std::invalid_argument("Cell is used!");

        short x{coordinates.x}, y{coordinates.y}, previous_x{coordinates.x}, previous_y{coordinates.y};

        for (size_t i = 1; i <= ship; ++i) {
            //TODO extra: ships should not touch each other

            //change x or y after head is set
            if (i > 1) {
                orientation == 'h' ? ++x : --y;
            }

            if (x > columns || y > rows) {
                throw std::invalid_argument("Broken boundary. Try placing your ship differently");
            }

            auto cell = playerOwnField.at(calculate_coord(x, y));

            if (cell != EMPTY) throw std::invalid_argument("Cell is used!");

//                if (isShipNearby(x, y)) {
//                    throw std::invalid_argument("Cannot place near ship!");
//                }

            playerOwnField[calculate_coord(x, y)] = CellType::SHIP;

            std::cerr << "placing ship at:" << calculate_coord(x, y) << std::endl;
        }

        std::cerr << "placing ship at:" << calculate_coord(coordinates.x, coordinates.y) << std::endl;

        return true;
    } catch (std::out_of_range const &of_range) {
        std::cerr << "Out of range:" << of_range.what() << std::endl;
        return false;
    } catch (std::invalid_argument const &invalid) {
        std::cerr << "Cell is not valid:" << invalid.what() << std::endl;
        return false;
    }
}
