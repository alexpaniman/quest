#pragma once

#include <iostream>

#include "fmt/core.h"
#include "game-map.h"
#include "action.h"
#include "quest/player.h"

namespace quest {

    class game {
    public:
        game(int cols, int rows);
        void run();

    private:
        quest::game_map map_;
        quest::player player_;

        void describe_feelings();
        void ask_to_act();
        void ask_to_move();
    };

}
