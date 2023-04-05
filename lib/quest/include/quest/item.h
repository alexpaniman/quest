#pragma once

#include <string>

namespace quest {

    class player;

    class item {
    public:
        virtual std::string describe() = 0;
        virtual void interact(quest::player &player) = 0;

        virtual ~item() = default;
    };

}
