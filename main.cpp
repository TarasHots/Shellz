#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <stdexcept>
#include <memory>
#include "utils.h"

enum CellType
{
    EMPTY = 0,
    SHIP = 1,
    DAMAGED = 2,
    MISS = 3
};

struct Coordinates
{
    size_t x, y;

    Coordinates(size_t x, size_t y)
    {
        this->x = x;
        this->y = y;
    }
};

struct CommandTranslator
{
public:
    /*
     * let's stick to the following format:
     * place ship - place a5(where) 3(ship type) v(orientation)
     * shoot - shoot c3(where)
     */
    explicit CommandTranslator(std::string &command)
    {
        command = command.erase(0,6);

        //TODO read 10!
        coordinates = command.substr(0, 2);
        ship = command[3] - '0';
        orientation = command[5];
    }

    size_t get_ship()
    {
        return ship;
    }

    char get_orientation()
    {
        return orientation;
    }

    Coordinates* get_coordinates()
    {
        //2d access: [i*column_size + j]
        auto coordinate_column = letters_mapping[coordinates[0]];
        auto coordinate_row = coordinates[1] - '0';

        return new Coordinates(coordinate_column, coordinate_row);
    }
private:
    std::string coordinates {};
    size_t ship {};
    char orientation {};
    std::map<char, size_t> letters_mapping = { {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}, {'f', 6},{'g', 7},{'h', 8}, {'i',9}, {'j', 10} };
};

struct PlayField
{
public:
    bool placeShip(std::string placement)
    {
        auto command = std::make_unique<CommandTranslator>(placement);

        return place(command->get_coordinates(), command->get_ship(), command->get_orientation());
    }

    void display()
    {
        std::string letters_row { "  | A | B | C | D | E | F | G | H | I | J |" };
        std::string delimiter { "-------------------------------------------" };

        std::cout << letters_row << std::endl;

        short cells_count = 1, max = columns, row_counter = 1;

        std::cout << row_counter << " | ";

        for (auto cell : playerOwnField)
        {
            if (cells_count == max)
            {
                std::cout << cell << " | " << std::endl;

                cells_count = 1;

                if (row_counter < max)
                {
                    row_counter++;
                    std::cout << row_counter << (row_counter >= 10 ? "| " : " | ");
                }

                continue;
            };

            std::cout << cell << " | ";
            ++cells_count;
        }
    }
private:
    short columns = 10;
    short rows = 10;

    std::vector<CellType> playerOwnField = std::vector<CellType>(columns * rows);
    std::vector<CellType> playerShootingField = std::vector<CellType>(columns * rows);

    size_t calculate_coord(size_t x, size_t y)
    {
        return columns * --y + --x;
    }

    bool place(const Coordinates* coordinates, const size_t &ship, const char &orientation)
    {
        try
        {
            auto first_cell = playerOwnField.at(calculate_coord(coordinates->x, coordinates->y));

            if (first_cell != EMPTY) throw std::invalid_argument("Cell is used!");

            size_t x { coordinates->x }, y { coordinates->y };

            for (size_t i = 1; i < ship; ++i)
            {
                //TODO extra: ships should not touch each other
                //TODO boundaries are not checked, do manually
                orientation == 'h' ? ++x : ++y;

                auto cell = playerOwnField.at(calculate_coord(x, y));

                if (cell != EMPTY) throw std::invalid_argument("Cell is used!");

                playerOwnField[calculate_coord(x, y)] = CellType::SHIP;

                std::cerr << "placing ship at:" << calculate_coord(x, y) << std::endl;
            }

            playerOwnField[calculate_coord(coordinates->x, coordinates->y)] = CellType::SHIP;

            std::cerr << "placing ship at:" << calculate_coord(coordinates->x, coordinates->y) << std::endl;

            return true;
        } catch (std::out_of_range const &of_range) {
            std::cerr << "Out of range:" << of_range.what() << std::endl;
            return false;
        } catch (std::invalid_argument const &invalid) {
            std::cerr << "Cell is not valid:" << invalid.what() << std::endl;
            return false;
        }
    }
};

int main() {
    auto playerField1 = std::make_unique<PlayField>();
    playerField1->placeShip("place h9 4 v");
    playerField1->display();

    return 0;
}
