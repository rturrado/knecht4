#pragma once

#include "knecht4/match_manager.hpp"

namespace k4 {

class GameManager {
public:
    static GameManager& get_instance() {
        static GameManager instance;
        return instance;
    }

    void run ();
};

}  // namespace k4
