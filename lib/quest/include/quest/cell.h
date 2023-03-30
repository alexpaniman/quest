#pragma once

#include "item.h"
#include <optional>

namespace quest {

    class player;

    struct cell {
        enum its_kind { wumpus, hole, regular } kind;
        item *item;

        void on_enter(player *player) const;
        std::optional<std::string> get_feeling() const;
    };

}
