#include "knecht4/piece.hpp"

namespace k4 {

std::ostream& operator<<(std::ostream& os, const Piece& piece) {
    return os << (piece == Piece::red ? "+" : "-");
}

}  // namespace k4
