#pragma once

#include <cstdint>  // uint8_t
#include <fmt/ostream.h>
#include <ostream>

namespace k4 {

enum class Piece : std::uint8_t {
    red = 0,
    yellow = 1
};

std::ostream& operator<<(std::ostream& os, const Piece& piece);

}  // namespace k4

template <>
struct fmt::formatter<k4::Piece> : ostream_formatter {};
