#pragma once

#include <iostream>

#include "fmt/core.h"
#include "game-map.h"
#include "action.h"
#include "quest/player.h"

namespace quest {

    class game {
    public:
        game(quest::game_map map);
        void run();

    private:
        void print_map();
        void print_player_stats();

        void describe_feelings();
        void ask_to_act();
        void ask_to_move();

        quest::game_map map_;
        quest::player player_;

        bool is_running_;
    };

}
