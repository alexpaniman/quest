#pragma once

#include "quest/action.h"
#include "quest/game-map.h"

#include "fmt/color.h"
#include "fmt/core.h"

#include <string>
#include <set>


namespace quest {

    class player {
    public:
        player(quest::proxy_cell cell, int max_hp);

        std::vector<quest::action> get_available_actions();
        std::set<std::string> get_feelings();

        void notify(fmt::string_view format, auto&&... printed_data) {
            // TODO: move this to game, so it's possible to easily reimplement UI
            std::string message = fmt::vformat(format,
                fmt::make_format_args(
                    std::forward<decltype(printed_data)>(printed_data)...)); 

            fmt::print(fg(fmt::color::indian_red) | fmt::emphasis::bold, "\n! {}", message);
        }

        quest::proxy_cell position() { return current_cell_; }
        void move(quest::move_direction direction);

        bool is_alive();

        int hp() { return hp_; }
        void heal(int hp);
        void damage(int hp);

    private:
        quest::proxy_cell current_cell_;
        int max_hp_, hp_;
    };

}
