#pragma once

#include "item.h"
#include <memory>
#include <optional>

namespace quest {

    class player;

    class cell {
    public:
        enum its_kind { wumpus, hole, regular } kind = regular;
        std::unique_ptr<item> item = nullptr;

        void on_enter(player *player);
        std::optional<std::string> get_feeling() const;

        bool visited() const { return visited_; }

    private:
        bool visited_;
    };

}
