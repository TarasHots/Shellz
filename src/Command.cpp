#include "Command.h"

using namespace Battleships;

Command::Command(std::string_view &command)
{
    auto commandArgs = BattleshipsUtils::split(command);

    if (commandArgs.empty() || commandArgs.size() != Command::EXPECTED_ARGUMENTS_COUNT) {
        throw std::invalid_argument("Provided command arguments are not correct!");
    }

    command = commandArgs.at(0);
    coordinates = commandArgs.at(1);

    std::stringstream ship_string(commandArgs.at(2));
    std::stringstream orientation_string(commandArgs.at(3));
    ship_string >> ship;
    orientation_string >> orientation;
}

Coordinates Command::get_coordinates() {
    //2d access: [i*column_size + j]
    auto coordinate_column = letters_mapping[coordinates[0]];
    size_t coordinate_row{};

    std::stringstream row_string(static_cast<std::string>(coordinates.substr(1, 2)));
    row_string >> coordinate_row;

    Coordinates coordinates_result(coordinate_column, coordinate_row);

    return coordinates_result;
}