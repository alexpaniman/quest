#include "quest/player.h"
#include "quest/action.h"
#include "quest/cell.h"
#include "quest/game-map.h"

#include "fmt/format.h"

namespace quest {

    player::player(quest::game_map &map, int max_hp):
        map_(map), max_hp_(max_hp), hp_(max_hp) {}


    std::vector<action> player::get_available_actions() {
        std::vector<action> actions;
        if (get_current_cell().item != nullptr) {
            // There's an item in the cell
            actions.push_back({ get_current_cell().item->describe(),
                [this] {
                    get_current_cell().item->interact(*this);
                }
            });
        }

        actions.push_back({ "do nothing", [] {} });

        return actions;
    }


    void player::lookup_feeling(int row, int col, std::set<std::string> &feelings) {
        if (can_move_to(row, col)) {
            auto feeling = map_[row][col].get_feeling();
            feelings.insert(*feeling);
        }
    }

    std::set<std::string> player::get_feelings() {
        std::set<std::string> feelings;

        lookup_feeling(pos_.col + 1, pos_.col - 1, feelings);
        lookup_feeling(pos_.col - 1, pos_.col - 1, feelings);
        lookup_feeling(pos_.col - 1, pos_.col + 1, feelings);
        lookup_feeling(pos_.col + 1, pos_.col + 1, feelings);
        return feelings;
    }


    bool player::is_alive() { return hp_ > 0; }

    void player::heal(int hp) {
        hp_ = std::min(hp_ + hp, max_hp_);
    }

    void player::damage(int hp) {
        hp_ = std::max(hp_ - hp, 0);

        notify("You recieved {} damage!\n", hp);
        if (hp_ == 0)
            notify("Congratulations! You failed! You are dead now!\n");
    }


    bool player::can_move_to(int col, int row) {
        return col >= 0 && col < map_.cols() && row >= 0 && row < map_.rows();
    }

    void player::move_to(move_direction direction) {
        position old_pos = pos_;

        switch (direction) {
        case move_direction::UP:
            pos_.row ++;
            break;

        case move_direction::DOWN:
            pos_.row ++;
            break;

        case move_direction::LEFT:
            pos_.col --;
            break;

        case move_direction::RIGHT:
            pos_.col ++;
            break;
        };

        if (can_move_to(pos_.col, pos_.row)) {
            notify("You can't go there! There's a wall in the way!\n");
            pos_ = old_pos;
        }
    }

    quest::cell player::get_current_cell() {
        return map_[pos_.row][pos_.col];
    }


}
