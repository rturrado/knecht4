#pragma once

#include <memory>  // unique_ptr

#include "knecht4/board.hpp"
#include "knecht4/player.hpp"

namespace k4 {

class MatchManager {
public:
    static MatchManager& get_instance() {
        static MatchManager instance;
        return instance;
    }

    void run();

private:
    MatchManager();

private:
    std::unique_ptr<Board> board_ = nullptr;
    std::array<std::unique_ptr<Player>, 2> players_ = { nullptr, nullptr };
};

}  // namespace k4
