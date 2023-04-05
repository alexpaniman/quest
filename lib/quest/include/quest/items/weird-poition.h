#pragma once

#include "quest/game-map.h"
#include "quest/item.h"
#include "quest/player.h"

namespace quest {

    class weird_poition: public quest::item {
    public:
        std::string describe() override { return "Drink weird potion"; }
        void interact(quest::player &player) override {
            if (rand() % 2 == 0)
                player.heal(1);
            else
                player.damage(1);
        }
    };

}
