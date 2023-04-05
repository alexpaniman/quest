#include "quest/game-map.h"

namespace quest {

    game_map::game_map(std::initializer_list<std::string> map):
        game_map(map.size(), map.begin()->size()) {

        int count_default_position_set = 0;

        int row_index = rows() - 1;
        for (auto row: map) {

            int col_index = 0;
            for (auto element: row) {
                cell::its_kind &kind = get_cell(row_index, col_index).kind;
                switch (element) {
                case '.':
                    kind = cell::regular;
                    break;

                case 'w':
                    kind = cell::wumpus;
                    break;

                case 'o':
                    kind = cell::hole;
                    break;

                case '#':
                    initial_col_ = col_index;
                    initial_row_ = row_index;
                    ++ count_default_position_set;

                    break;

                default:
                    throw axp::exception { "Illegal map format specifier: {}", kind };
                    // TODO: can be checked during compile time!
                }

                ++ col_index;
            }

            -- row_index;
        }

        if (count_default_position_set != 1)
            throw axp::exception { "Default position should be set only once, but set: {}!",
                                    count_default_position_set };
    }

};
