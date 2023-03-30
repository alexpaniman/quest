#pragma once

#include "cell.h"
#include <vector>

namespace quest {

    class game_map {
    public:
        game_map(int rows, int cols):
            cells_(rows, std::vector<cell>(cols)) {}

        const std::vector<cell>& operator[](int row) { return cells_[row]; }

        int rows() const { return rows_; }
        int cols() const { return cols_; }

    private:
        int rows_, cols_;

        // TODO: make into linear container:
        std::vector<std::vector<cell>> cells_;
    };

}
