#pragma once

#include <cstdint>  // uint8_t

#include "knecht4/utils/console.hpp"

namespace k4 {

class Player {
public:
    virtual ~Player() = default;
    [[nodiscard]] virtual std::uint8_t move() = 0;
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
