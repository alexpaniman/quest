#pragma once

#include "player.h"
#include <string>

namespace quest {

    class item {
    public:
        virtual std::string describe() = 0;
        virtual void interact(quest::player &player) = 0;
    };

}
