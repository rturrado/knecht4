#include "knecht4/turn.hpp"

#include <ostream>

namespace k4 {

std::ostream& operator<<(std::ostream& os, const Turn& turn) {
    return os << (turn == Turn::machine ? "Machine" : "User");
}

}  // namespace k4
