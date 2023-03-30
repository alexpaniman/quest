#include "fmt/format.h"
#include "quest/game.h"
#include "quest/player.h"

quest::game_map build_simple_map() {
    quest::game_map map(10, 10);
}


int main() {
    fmt::print("And there it begins!\n");
        
    quest::game game(10, 10);
    game.run();
}
