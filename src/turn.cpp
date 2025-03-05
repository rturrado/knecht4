#include "knecht4/turn.hpp"

#include <ostream>

namespace k4 {

std::uint8_t to_underlying(Turn turn) {
    return static_cast<std::uint8_t>(turn);
}

Turn next(Turn turn) {
    return turn == Turn::machine ? Turn::user : Turn::machine;
}

std::ostream& operator<<(std::ostream& os, const Turn& turn) {
    return os << (turn == Turn::machine ? "Machine" : "User");
}

}  // namespace k4
