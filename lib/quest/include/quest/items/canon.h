#pragma once

#include "quest/cell.h"
#include "quest/game-map.h"
#include "quest/item.h"
#include "quest/player.h"


namespace quest {

    class cannon: public quest::item {
    public:
        std::string describe() override { return "Kill all wampuses around"; }
        void interact(quest::player &player) override {
            for (auto direction: quest::directions()) {
                quest::cell &current = player.position().move(direction).data();
                if (current.kind == quest::cell::wumpus) {
                    current.kind = quest::cell::regular;
                    player.notify("Congrats! You killed wumpus nearby!");
                }
            }
        }
    };

}
