#include "quest/player.h"
#include "quest/action.h"
#include "quest/cell.h"
#include "quest/game-map.h"

#include "fmt/format.h"

namespace quest {

    player::player(quest::proxy_cell cell, int max_hp):
        current_cell_(cell), max_hp_(max_hp), hp_(max_hp) {

        // should visit cell we're created in:
        current_cell_.data().on_enter(this);
    }


    std::vector<action> player::get_available_actions() {
        std::vector<action> actions;

        using enum move_direction;
        for (auto direction: directions())
            actions.push_back({
                fmt::format("Move {}", direction_names.at(direction) ),
                [this, direction] { move(direction); }
            });

        cell &cell = current_cell_.data();
        if (cell.item != nullptr) {

            // There's an item in the cell
            actions.push_back({
                cell.item->describe(),
                [this] {
                    current_cell_.data().item->interact(*this);

                    // item gets used up when you interact!
                    current_cell_.data().item = nullptr;
                }
            });
        }

        // Yep, that's always an option
        actions.push_back({ "Do nothing", [] {} });

        return actions;
    }


    std::set<std::string> player::get_feelings() {
        std::set<std::string> feelings;

        auto add_feeling = [&](move_direction direction) {
            proxy_cell cell = current_cell_.move(direction);
            if (cell) {
                auto feeling = cell.data().get_feeling();

                if (feeling)
                    feelings.insert(*feeling);
            }
        };

        using enum move_direction;
        for (auto direction: directions())
            add_feeling(direction);

        return feelings;
    }


    bool player::is_alive() { return hp_ > 0; }

    void player::heal(int hp) {
        notify("You healed {} hp!", hp);
        hp_ = std::min(hp_ + hp, max_hp_);
    }

    void player::damage(int hp) {
        hp_ = std::max(hp_ - hp, 0);

        notify("You recieved {} damage!", hp);
        if (hp_ == 0)
            notify("Congratulations! You failed! You are dead now!\n");
    }


    void player::move(move_direction direction) {
        proxy_cell next = current_cell_.move(direction);
        if (!next)
            notify("You can't go there! There's a wall in the way!");
        else {
            current_cell_ = next;
            current_cell_.data().on_enter(this);
        }
    }

}
