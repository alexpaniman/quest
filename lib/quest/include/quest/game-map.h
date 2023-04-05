#pragma once

#include "axp/exceptions.h"
#include "cell.h"

#include <initializer_list>
#include <array>
#include <vector>
#include <map>

namespace quest {

    // Let's do with this enum all the things C++ should
    // have done by default, but didn't:

    enum class move_direction { UP, DOWN, LEFT, RIGHT };
    inline const std::map<move_direction, std::string> direction_names = {
        { move_direction::UP,       "up" },
        { move_direction::DOWN,   "down" },
        { move_direction::LEFT,   "left" },
        { move_direction::RIGHT, "right" },
    };

    inline auto directions() {
        using enum move_direction;
        return std::array { UP, DOWN, LEFT, RIGHT };
    }


    class game_map;

    class proxy_cell {
    public:
        proxy_cell right();
        proxy_cell  left();
        proxy_cell    up();
        proxy_cell  down();

        quest::game_map& map() { return *map_; };

        proxy_cell move(move_direction direction);
        bool operator==(const proxy_cell &other) const {
            return row_ == other.row_ && col_ == other.col_;
        }

        cell& data();

        operator bool();

    private:
        friend class game_map;

        proxy_cell(quest::game_map *map, int row, int col):
            row_(row), col_(col), map_(map) {}

        int row_, col_;
        quest::game_map *map_;
    };


    class game_map {
    public:
        game_map(int rows, int cols): rows_(rows), cols_(cols), cells_(rows * cols) {}

        // construct map inline, use 'w' to denote wumpus,
        // 'o' to deonte hole and '.' to denote regular map
        game_map(std::initializer_list<std::string> map);

    private:
        // proxy class for overloaded []
        class proxy_row {
        public:
            proxy_cell operator[](int j) { return { &map_, index_, j }; }

        private:
            friend class game_map;

            // make it so noone except game_map can
            // construct this proxy:
            proxy_row(quest::game_map &map, int index):
                index_(index), map_(map) {}

            int index_; // index of selected with [] row
            quest::game_map &map_;
        };

    public:
        proxy_row operator[](int i) {  return { *this, i }; }

        int rows() const { return rows_; }
        int cols() const { return cols_; }

        proxy_cell initial_poisition() { return (*this)[initial_row_][initial_col_]; }

    private:
        friend class proxy_cell;

        int rows_, cols_;
        std::vector<cell> cells_;

        int initial_row_ = 0, initial_col_ = 0;

        cell &get_cell(int i, int j) { return cells_[i * cols() + j]; }
    };


    inline proxy_cell proxy_cell::right() { return { map_, row_, col_ + 1 }; }
    inline proxy_cell proxy_cell:: left() { return { map_, row_, col_ - 1 }; }
    inline proxy_cell proxy_cell::   up() { return { map_, row_ + 1, col_ }; }
    inline proxy_cell proxy_cell:: down() { return { map_, row_ - 1, col_ }; }

    inline proxy_cell proxy_cell::move(move_direction direction) {
        switch (direction) {
        case move_direction::UP:    return    up();
        case move_direction::DOWN:  return  down();
        case move_direction::LEFT:  return  left();
        case move_direction::RIGHT: return right();
        };
    }

    inline cell& proxy_cell::data() {
        return map_->get_cell(row_, col_);
    }

    inline proxy_cell::operator bool() {
        return col_ >= 0 && col_ < map_->cols() && row_ >= 0 && row_ < map_->rows();
    }

}
