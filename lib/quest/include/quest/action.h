#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace quest {

    struct action {
        std::string name;
        std::function<void()> act;
    };

}
