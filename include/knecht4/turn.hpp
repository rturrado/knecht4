#pragma once

#include <cstdint>  // uint8_t
#include <fmt/ostream.h>
#include <ostream>

namespace k4 {

enum class Turn : std::uint8_t {
    machine = 0,
    user = 1
};

std::uint8_t to_underlying(Turn turn);

Turn next(Turn turn);

std::ostream& operator<<(std::ostream& os, const Turn& turn);

}  // namespace k4

template <>
struct fmt::formatter<k4::Turn> : ostream_formatter {};
