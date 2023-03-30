#include "quest/cell.h"
#include "quest/player.h"

#include <optional>
#include <cassert>

namespace quest {

    void cell::on_enter(player *player) const {
        if (kind == regular)
            return;

        if (kind == wumpus)
            fmt::print("Oh no! There's a wumpus there!");

        if (kind == hole)
            fmt::print("Oh no! You fell in hole!");

        if (player->is_alive()) {
            fmt::print("Fortunately you were able to survive\n");
            fmt::print("But be careful next time!\n");
        }
    }

    std::optional<std::string> cell::get_feeling() const {
        if (kind == wumpus)
            return "smell";

        if (kind == hole)
            return "wind";

        return std::nullopt;
    }

}
