#include "knecht4/match_manager.hpp"

#include "knecht4/player.hpp"
#include "knecht4/turn.hpp"
#include "knecht4/utils/console.hpp"

namespace k4 {

std::unique_ptr<Player>& MatchManager::get_current_player() {
    return players_[to_underlying(turn_)];
}

std::unique_ptr<Player>& MatchManager::get_next_player() {
    return players_[to_underlying(next(turn_))];
}

void MatchManager::run() {
    board_->reset();

    // Choose starting turn
    turn_ = (utils::read_char("User starts or machine starts? [u/m] ", "um") == 'u')
        ? Turn::user
        : Turn::machine;
    get_current_player()->color(Piece::red);
    get_next_player()->color(Piece::yellow);
    fmt::print("{} starts with '{}' pieces\n", turn_, Piece::red);

    // Print board
    board_->print();

    for (;;) {
        // Choose player
        auto& player = get_current_player();

        // Insert piece
        auto column_index = player->move();
        fmt::print("{} inserts a '{}' piece in column {}\n", turn_, player->color(), column_index + 1);
        if (board_->full_column(column_index)) {
            fmt::print("\tError: column {} is full\n", column_index + 1);
            continue;
        }
        auto row_index = board_->insert(column_index, player->color());

        // Print board
        board_->print();

        // Check for end of game
        if (auto line = board_->check({ row_index, column_index }); line) {
            fmt::print("End of game: {} wins!\n", turn_);
            break;
        }
        if (board_->full()) {
            fmt::print("End of game: draw!\n");
            break;
        }

        // Change turn
        turn_ = next(turn_);
    }
}

}  // namespace k4
