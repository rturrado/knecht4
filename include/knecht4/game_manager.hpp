#pragma once

#include "knecht4/match_manager.hpp"

#include <iosfwd>

namespace k4 {

class GameManager {
public:
    static GameManager& get_instance(std::istream& is, std::ostream& os);
    void run ();

private:
    GameManager(std::istream& is, std::ostream& os);

private:
    std::istream& is_;
    std::ostream& os_;
};

}  // namespace k4
