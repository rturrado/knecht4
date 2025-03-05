#include "knecht4/player.hpp"

#include "knecht4/utils/console.hpp"
#include "knecht4/utils/random.hpp"

namespace k4 {

[[nodiscard]] std::uint8_t Machine::move() {
    return static_cast<std::uint8_t>(utils::RandomInt{ 0, 6 }());
}

[[nodiscard]] std::uint8_t User::move() {
    return utils::read_char("Choose a column [1/2/3/4/5/6/7] ", "1234567") - '1';
}

}  // namespace k4
