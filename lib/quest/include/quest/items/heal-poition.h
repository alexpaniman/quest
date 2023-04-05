#pragma once

#include "quest/game-map.h"
#include "quest/item.h"
#include "quest/player.h"


namespace quest {

    class heal_poition: public quest::item {
    public:
        std::string describe() override { return "Drink heal potion"; }
        void interact(quest::player &player) override {
            player.heal(1);
        }
    };

}
