#pragma once

#include <cstdint>  // uint8_t

#include "knecht4/piece.hpp"

namespace k4 {

class Player {
    Piece piece_;
public:
    virtual ~Player() = default;
    [[nodiscard]] virtual std::uint8_t move() = 0;
    [[nodiscard]] Piece color() const;
    void color(Piece piece);
};

class Machine : public Player {
public:
    [[nodiscard]] std::uint8_t move() override;
};

class User : public Player {
public:
    [[nodiscard]] std::uint8_t move() override;
};

}  // namespace k4
