#include "knecht4/game_manager.hpp"

#include "knecht4/utils/console.hpp"
#include "knecht4/match_manager.hpp"

#include <iostream>

namespace k4 {

/* static */ GameManager& GameManager::get_instance(std::istream& is, std::ostream& os) {
    static GameManager instance{is, os};
    return instance;
}

GameManager::GameManager(std::istream& is, std::ostream& os)
: is_{ is }
, os_{ os }
{}

void GameManager::run() {
    auto& match_manager = MatchManager::get_instance(is_, os_);
    while (utils::read_char(is_, os_, "Play or quit? [p/q] ", "pq") == 'p') {
        match_manager.query_turn();
        match_manager.run();
        match_manager.reset();
    }
}

}  // namespace k4
