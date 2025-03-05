#include "knecht4/turn.hpp"

#include <ostream>

namespace k4 {

std::ostream& operator<<(std::ostream& os, const Turn& turn) {
    switch (turn) {
        case Turn::machine: os << "Machine"; break;
        case Turn::user: os << "User"; break;
        default: break;
    }
    return os;
}

}  // namespace k4
