#include "quest/game.h"
#include "fmt/color.h"
#include "quest/game-map.h"

#include "axp/strings.h"
#include "quest/item.h"
#include <sstream>

namespace quest {

    using enum fmt::color;
    using enum fmt::emphasis;

    game::game(quest::game_map map):
        map_(std::move(map)),
        player_(map_.initial_poisition(), 3 /* TODO: default health */),
        is_running_(true) {}

    void game::print_map() {
        const int len = map_.cols() + 2 /* spaces around */;

        fmt::print("{}", "┌" + repeat("─", len) + "┐\n");

        for (int i = map_.rows() - 1; i >= 0; -- i) {
            fmt::print("│ ");

            for (int j = 0; j < map_.cols(); ++ j) {
                quest::proxy_cell cell = map_[i][j];
                if (cell == player_.position()) {
                    fmt::print(fg(indian_red) | bold, "#");
                    continue;
                }

                if (cell.data().visited())
                    fmt::print(fg(light_sea_green), ".");
                else
                    fmt::print(".");
            }

            fmt::print(" │\n");
        }

        fmt::print("{}", "└" + repeat("─", len) + "┘\n\n");
    }

    void game::print_player_stats() {
        fmt::print(fg(pale_green) | bold, "Your health: ");
        fmt::print(fg(indian_red) | bold, "{}", player_.hp());
    }

    void game::run() {
        while (player_.is_alive() && is_running_) {
            fmt::print("\n");

            print_map();
            print_player_stats();

            describe_feelings();
            ask_to_act();
        }
    }

    void game::describe_feelings() {
        auto feelings = player_.get_feelings();

        fmt::print(fg(sky_blue) | bold, "\nYou feel: ");
        for (auto &&feeling: feelings)
            fmt::print("{}", feeling);

        if (feelings.empty())
            fmt::print("well, nothing");

        fmt::print("\n");
    }

    void game::ask_to_act() {
        auto actions = player_.get_available_actions();

        fmt::print(bold | fg(sky_blue), "\nYou have {} choices:\n", actions.size());
        for (int i = 0; i < static_cast<int>(actions.size()); ++ i) {
            fmt::print(fg(alice_blue) | bold, "{}", i);
            fmt::print(". ");
            fmt::print(fg(light_steel_blue), "{}\n", actions[i].name);
        }

        fmt::print("\n");

        fmt::print(fg(indian_red) | bold, "q");
        fmt::print(". ");
        fmt::print("Quit\n");

        while (true) {
            fmt::print(fg(sky_blue) | bold, "\nSelect: ");

            std::string line;
            std::getline(std::cin, line);

            if (line == "q") {
                is_running_ = false;
                return;
            }

            std::istringstream iss(line);
            int selection;

            if ((iss >> selection) && selection >= 0 && selection < static_cast<int>(actions.size())) {
                actions[selection].act();
                break;
            }

            fmt::print("What did you type?! I didn't get! Try again!\n");
        }
    }

    void game::ask_to_move() {
        fmt::print("Do you want to move?");
    }

}
