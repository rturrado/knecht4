#include "knecht4/match_manager.hpp"

#include "knecht4/player.hpp"
#include "knecht4/turn.hpp"
#include "knecht4/utils/console.hpp"

#include <fmt/ostream.h>

namespace k4 {

/* static */ MatchManager& MatchManager::get_instance(std::istream& is, std::ostream& os) {
    static MatchManager instance{ is, os };
    return instance;
}

MatchManager::MatchManager(std::istream &is, std::ostream &os)
: is_{ is }
, os_{ os }
, board_{ std::make_unique<Board>() }
, players_{ std::make_unique<Machine>(is, os), std::make_unique<User>(is, os) }
, turn_{ Turn::machine }
{}

std::unique_ptr<Player>& MatchManager::get_current_player() {
    return players_[to_underlying(turn_)];
}

std::unique_ptr<Player>& MatchManager::get_next_player() {
    return players_[to_underlying(next(turn_))];
}

void MatchManager::set_board(std::unique_ptr<Board> board) {
    board_ = std::move(board);
}

void MatchManager::set_turn(Turn turn) {
    turn_ = std::move(turn);
}

void MatchManager::query_turn() {
    turn_ = (utils::read_char(is_, os_, "User starts or machine starts? [u/m] ", "um") == 'u')
        ? Turn::user
        : Turn::machine;
    get_current_player()->color(Piece::red);
    get_next_player()->color(Piece::yellow);
    fmt::print(os_, "{} starts with '{}' pieces\n", turn_, Piece::red);
}

void MatchManager::run() {
    // Print board
    board_->print();

    for (;;) {
        // Choose player
        auto& player = get_current_player();

        // Insert piece
        auto column_index = player->move();
        fmt::print(os_, "{} inserts a '{}' piece in column {}\n", turn_, player->color(), column_index + 1);
        if (board_->full_column(column_index)) {
            fmt::print(os_, "\tError: column {} is full\n", column_index + 1);
            continue;
        }
        auto row_index = board_->insert(column_index, player->color());

        // Print board
        board_->print();

        // Check for end of game
        if (auto line = board_->check({ row_index, column_index }); line) {
            fmt::print(os_, "End of game: {} wins!\n", turn_);
            fmt::print(os_, "+-+ Line: {} +-+\n", line.value());
            break;
        }
        if (board_->full()) {
            fmt::print(os_, "End of game: draw!\n");
            break;
        }

        // Change turn
        turn_ = next(turn_);
    }
}

void MatchManager::reset() {
    board_->reset();
    turn_ = Turn::machine;
}

}  // namespace k4
