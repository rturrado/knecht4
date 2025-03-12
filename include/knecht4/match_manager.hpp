#pragma once

#include <iosfwd>
#include <memory>  // unique_ptr

#include "knecht4/board.hpp"
#include "knecht4/player.hpp"
#include "knecht4/turn.hpp"

namespace k4 {

class MatchManager {
    std::unique_ptr<Player>& get_current_player();
    std::unique_ptr<Player>& get_next_player();

public:
    static MatchManager& get_instance(std::istream& is, std::ostream& os);
    void set_board(std::unique_ptr<Board> board);
    void set_turn(Turn turn);
    void query_turn();
    void run();
    void reset();

private:
    MatchManager(std::istream& is, std::ostream& os);

private:
    std::istream& is_;
    std::ostream& os_;

private:
    std::unique_ptr<Board> board_;
    std::array<std::unique_ptr<Player>, 2> players_;
    Turn turn_;
};

}  // namespace k4
