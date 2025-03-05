#include "knecht4/game_manager.hpp"

#include "knecht4/utils/console.hpp"
#include "knecht4/match_manager.hpp"

namespace k4 {

void GameManager::run() {
    while (utils::read_char("Play or quit? [p/q] ", "pq") == 'p') {
        MatchManager::get_instance().run();
    }
}

}  // namespace k4
