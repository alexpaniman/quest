#include "fmt/color.h"
#include "fmt/format.h"
#include "quest/game-map.h"
#include "quest/game.h"
#include "quest/items/weird-poition.h"
#include "quest/player.h"

#include "quest/items/canon.h"
#include "quest/items/heal-poition.h"


quest::game_map build_map() {
    quest::game_map map {
        "w.......................",
        "........................",
        ".......w................",
        "..............ooo.......",
        ".....................w..",
        ".....w..................",
        "............w........w..",
        "...o...............oo...",
        "......o..o..o..w........",
        "#w.o...............w...."
    };

    auto add_item = [&](int i, int j, quest::item *new_item) {
        map[i][j].data().item.reset(new_item);
    };

    // TODO: automatic system for item generation (and in 
    //       general map generation would be nice)

    add_item(1, 0, new quest::cannon);
    add_item(2, 2, new quest::heal_poition);
    add_item(0, 0, new quest::weird_poition);
    add_item(2, 3, new quest::cannon);

    return map;
}

void setup_random_generator() { std::srand(time(nullptr)); }

void print_intro() {
    fmt::print(fg(fmt::color::sky_blue) | fmt::emphasis::bold,
               "This is a text adventure game inspired by Hunt-the-Wumpus!\n"
               "You can explore the map, and kill wumpuses with items!\n\n");

    fmt::print(fg(fmt::color::light_sea_green) | fmt::emphasis::bold,
               "Good luck! I hope you enjoy!\n\n");

    fmt::print(fg(fmt::color::gray), 
               "Project's source code is available under MIT License on GitHub:\n"
               "    https://github.com/alexpaniman/quest\n\n"
               "You're welcome to check out code and write pull requests!\n");

    fmt::print(fmt::emphasis::bold, "Copyright (c) Alex Paniman 2023\n\n");
}


int main() {
    setup_random_generator();
    print_intro();

    quest::game_map map = build_map();
    quest::game game(std::move(map));
    game.run();
}
