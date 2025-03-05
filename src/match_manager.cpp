#include "knecht4/match_manager.hpp"

#include <memory>  // make_unique, unique_ptr

#include "knecht4/player.hpp"
#include "knecht4/turn.hpp"
#include "knecht4/utils/console.hpp"

namespace k4 {

MatchManager::MatchManager()
: board_{ std::make_unique<Board>() }
, players_{ std::make_unique<Machine>(), std::make_unique<User>() }
{}

void MatchManager::run() {
    board_->reset();

    // Choose starting turn
    auto turn = (utils::read_char("User starts or machine starts? [u/m] ", "um") == 'u')
        ? Turn::user
        : Turn::machine;
    fmt::print("{} starts with '{}' pieces\n", turn, board_->get_next_piece());

    for (;;) {
        // Choose player
        auto& player = players_[static_cast<size_t>(turn)];

        // Insert piece
        auto column_index = player->move();
        fmt::print("{} inserts a '{}' piece in column '{}'\n", turn, board_->get_next_piece(), column_index + 1);
        if (board_->full_column(column_index)) {
            fmt::print("\tError: column {} is full\n", column_index + 1);
            continue;
        }
        auto row_index = board_->insert(column_index);

        // Print board
        board_->print();

        // Check for end of game
        if (auto line = board_->check({ row_index, column_index });
            line.has_value()) {
            fmt::print("End of game: {} wins!\n", turn);
            break;
        }
        if (board_->full()) {
            fmt::print("End of game: draw!\n");
            break;
        }

        // Change turn
        turn = turn == Turn::machine ? Turn::user : Turn::machine;
    }
}

}  // namespace k4
