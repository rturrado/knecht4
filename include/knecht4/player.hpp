#pragma once

#include <cstdint>  // uint8_t

#include "knecht4/piece.hpp"

namespace k4 {

class Player {
public:
    Player(std::istream& is, std::ostream& os);
    virtual ~Player() = default;

public:
    [[nodiscard]] virtual std::uint8_t move() = 0;
    [[nodiscard]] Piece color() const;
    void color(Piece piece);

protected:
    std::istream& is_;
    std::ostream& os_;
    Piece piece_;
};

class Machine : public Player {
public:
    Machine(std::istream& is, std::ostream& os);

public:
    [[nodiscard]] std::uint8_t move() override;
};

class User : public Player {
public:
    User(std::istream& is, std::ostream& os);

public:
    [[nodiscard]] std::uint8_t move() override;
};

}  // namespace k4
