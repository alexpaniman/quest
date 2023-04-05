#include "quest/cell.h"
#include "quest/player.h"

#include <optional>

namespace quest {

    void cell::on_enter(player *player) {
        visited_ = true;

        if (kind == regular)
            return;

        if (kind == wumpus)
            player->notify("Oh no! There's a wumpus there!\n");

        if (kind == hole)
            player->notify("Oh no! You fell in hole!\n");

        player->damage(1);

        if (player->is_alive()) {
            player->notify("Fortunately you were able to survive");
            player->notify("But be careful next time!");
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
