#pragma once

#include <algorithm>  // all_of, count_if, fill
#include <array>
#include <cassert>  // assert
#include <cstdint>  // uint8_t
#include <fmt/ostream.h>
#include <numeric>  // accumulate
#include <optional>
#include <ostream>
#include <stdexcept>  // runtime_error

#include "knecht4/piece.hpp"

namespace k4 {

constinit const std::uint8_t number_of_columns = 7;
constinit const std::uint8_t number_of_rows = 6;
constinit const std::uint8_t minimum_line_size = 4;
constinit const std::uint8_t top_row_index = 0;
constinit const std::uint8_t bottom_row_index = 5;

using RowIndex = std::uint8_t;
using ColumnIndex = std::uint8_t;

struct CellIndex {
    RowIndex row;
    ColumnIndex column;
    auto operator<=>(const CellIndex& other) const = default;
};

struct Line {
    CellIndex start;
    CellIndex end;
    auto operator<=>(const Line& other) const = default;
};

struct BoardError : public std::runtime_error {
    explicit BoardError(const std::string& message) : std::runtime_error{ message } {}
};

class Board {
public:
    using Cell = std::optional<Piece>;
    using Row = std::array<Cell, number_of_columns>;
    using Matrix = std::array<Row, number_of_rows>;
    using RowIndices = std::array<RowIndex, number_of_columns>;

private:
    [[nodiscard]] std::optional<Line> check_vertical(const CellIndex& cell_index) const;
    [[nodiscard]] std::optional<Line> check_horizontal(const CellIndex& cell_index) const;
    [[nodiscard]] std::optional<Line> check_diagonal(const CellIndex& cell_index) const;
    [[nodiscard]] std::optional<Line> check_diagonal_top_down(const CellIndex& cell_index) const;
    [[nodiscard]] std::optional<Line> check_diagonal_bottom_up(const CellIndex& cell_index) const;

public:
    Board();
    explicit Board(const std::string& board);

public:
    void reset();
    void print() const;
    [[nodiscard]] RowIndex insert(ColumnIndex column_index, Piece piece);
    [[nodiscard]] std::optional<Line> check(const CellIndex& cell_index) const;
    [[nodiscard]] Cell get_cell(std::uint8_t row_index, std::uint8_t column_index) const;
    [[nodiscard]] bool full_column(ColumnIndex column_index) const;
    [[nodiscard]] bool full() const;

private:
    Matrix data_;
    RowIndices top_piece_row_indices_;
};

std::ostream& operator<<(std::ostream& os, const CellIndex& cell_index);
std::ostream& operator<<(std::ostream& os, const Line& line);
std::ostream& operator<<(std::ostream& os, const Board& board);

}  // namespace k4

template <>
struct fmt::formatter<k4::CellIndex> : ostream_formatter {};
template <>
struct fmt::formatter<k4::Line> : ostream_formatter {};
template <>
struct fmt::formatter<k4::Board> : ostream_formatter {};
