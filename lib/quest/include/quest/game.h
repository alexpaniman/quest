#pragma once

#include <iostream>

#include "fmt/core.h"
#include "game-map.h"
#include "action.h"
#include "quest/player.h"

namespace quest {

    class game {
    public:
        game(int cols, int rows):
            map_(cols, rows),
            player_(map_, 3) {}

        void run() {
            while (player_.is_alive()) {
                fmt::print("\n");
                describe_feelings();
                ask_to_act();
            }
        }

    private:
        quest::game_map map_;
        quest::player player_;

        void describe_feelings() {
            auto feelings = player_.get_feelings();

            fmt::print("You feel: ");
            for (auto &&feeling: feelings)
                fmt::print("{}", feeling);

            fmt::print("\n");
        }

        void ask_to_act() {
            auto actions = player_.get_available_actions();

            fmt::print("You have {} choices:\n", actions.size());
            for (int i = 0; i < actions.size(); ++ i)
                fmt::print("{}. {}\n", i, actions[i].name);

            fmt::print("Select: ");

            int selection; std::cin >> selection;

            actions[selection].act(); // Perform selected action
        }

        void ask_to_move() {
            fmt::print("Do you want to move?");
        }
    };

}
