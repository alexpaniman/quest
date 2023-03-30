#pragma once

#include "quest/action.h"

#include "fmt/core.h"
#include <string>
#include <set>


namespace quest {

    class cell;
    class game_map;

    enum class move_direction { UP, DOWN, LEFT, RIGHT };

    class player {
    public:
        player(quest::game_map &map, int max_hp);

        std::vector<quest::action> get_available_actions();
        std::set<std::string> get_feelings();

        void notify(fmt::string_view format, auto&&... printed_data) {
            // TODO: for now just print message
            fmt::vprint(format, fmt::make_format_args(
                std::forward<decltype(printed_data)>(printed_data)...));
        }

        void move_to(move_direction direction);

        bool is_alive();

        void heal(int hp);
        void damage(int hp);

    private:
        struct position { int row, col; };

        position pos_ = { 0, 0 };
        quest::game_map &map_;

        int max_hp_, hp_;

        quest::cell get_current_cell();
        bool can_move_to(int row, int col);

        void lookup_feeling(int row, int col, std::set<std::string> &feelings);
    };

}
