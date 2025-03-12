#include "knecht4/player.hpp"

#include "knecht4/utils/console.hpp"
#include "knecht4/utils/random.hpp"

namespace k4 {

Player::Player(std::istream& is, std::ostream& os)
: is_{ is }
, os_{ os }
{}

[[nodiscard]] Piece Player::color() const {
    return piece_;
}

void Player::color(Piece piece) {
    piece_ = piece;
}

Machine::Machine(std::istream& is, std::ostream& os)
: Player{ is, os }
{}

[[nodiscard]] std::uint8_t Machine::move() {
    return static_cast<std::uint8_t>(utils::RandomInt{ 0, 6 }());
}

User::User(std::istream& is, std::ostream& os)
: Player{ is, os }
{}

[[nodiscard]] std::uint8_t User::move() {
    return utils::read_char(is_, os_, "Choose a column [1/2/3/4/5/6/7] ", "1234567") - '1';
}

}  // namespace k4
