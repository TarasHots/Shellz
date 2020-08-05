#ifndef SHELLZ_COMMAND_H
#define SHELLZ_COMMAND_H

#include "definitions.h"
#include "../utils.h"

namespace Battleships
{
    struct Command
    {
    public:
        /*
         * let's stick to the following format:
         * place ship - place a5(where) 3(ship type) v(orientation)
         * shoot - shoot c3(where)
         */
        explicit Command(std::string_view &command);

        [[nodiscard]] size_t get_ship() const
        {
            return ship;
        }

        [[nodiscard]] char get_orientation() const
        {
            return orientation;
        }

        [[nodiscard]] std::string_view get_command() const
        {
            return command;
        }

        Coordinates get_coordinates();
    private:
        constexpr static int EXPECTED_ARGUMENTS_COUNT = 4;
        std::string_view command {};
        std::string_view coordinates {};
        size_t ship {};
        char orientation {};
        std::map<char, size_t> letters_mapping = { {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}, {'f', 6},{'g', 7},{'h', 8}, {'i',9}, {'j', 10} };
    };
}

#endif //SHELLZ_COMMAND_H
