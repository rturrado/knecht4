#pragma once

#include <memory>  // unique_ptr

#include "knecht4/board.hpp"
#include "knecht4/player.hpp"
#include "knecht4/turn.hpp"

namespace k4 {

class MatchManager {
    std::unique_ptr<Player>& get_current_player();
    std::unique_ptr<Player>& get_next_player();

public:
    static MatchManager& get_instance() {
        static MatchManager instance;
        return instance;
    }

    void run();

private:
    MatchManager() = default;

private:
    std::unique_ptr<Board> board_ = std::make_unique<Board>();
    std::array<std::unique_ptr<Player>, 2> players_ = { std::make_unique<Machine>(), std::make_unique<User>() };
    Turn turn_ = Turn::machine;
};

}  // namespace k4
