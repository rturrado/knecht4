#pragma once

#include <algorithm>  // all_of, count_if, fill
#include <array>
#include <cassert>  // assert
#include <cstdint>  // uint8_t
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <numeric>  // accumulate
#include <optional>
#include <ostream>
#include <stdexcept>  // runtime_error

namespace k4 {

constinit const std::uint8_t number_of_columns = 7;
constinit const std::uint8_t number_of_rows = 6;
constinit const std::uint8_t minimum_line_size = 4;

enum class Piece : std::uint8_t {
    red = 0,
    yellow = 1
};

std::ostream& operator<<(std::ostream& os, const Piece& piece);

using RowIndex = std::uint8_t;
using ColumnIndex = std::uint8_t;

struct CellIndex {
    RowIndex row;
    ColumnIndex column;
};

struct Line {
    CellIndex start;
    CellIndex end;
};

struct BoardError : public std::runtime_error {
    explicit BoardError(const std::string& message) : std::runtime_error{ message } {}
};

class Board {
public:
    using Cell = std::optional<Piece>;
    using Row = std::array<Cell, number_of_columns>;
    using Matrix = std::array<Row, number_of_rows>;

private:
    [[nodiscard]] std::optional<Line> check_vertical(const CellIndex& cell_index) const;
    [[nodiscard]] std::optional<Line> check_horizontal(const CellIndex& cell_index) const;
    [[nodiscard]] std::optional<Line> check_diagonal(const CellIndex& cell_index) const;
    [[nodiscard]] std::optional<Line> check_diagonal_top_down(const CellIndex& cell_index) const;
    [[nodiscard]] std::optional<Line> check_diagonal_bottom_up(const CellIndex& cell_index) const;
    [[nodiscard]] std::uint8_t get_number_of_empty_rows(ColumnIndex column_index) const;

public:
    Board();
    void reset();
    void print() const;
    [[nodiscard]] RowIndex insert(ColumnIndex column_index);
    [[nodiscard]] std::optional<Line> check(const CellIndex& cell_index) const;
    [[nodiscard]] Cell get_cell(std::uint8_t row_index, std::uint8_t column_index) const;
    [[nodiscard]] Piece get_next_piece() const;
    [[nodiscard]] bool full_column(ColumnIndex column_index) const;
    [[nodiscard]] bool full() const;

private:
    Matrix data_;
    Piece next_piece_;
};

std::ostream& operator<<(std::ostream& os, const Board& board);

}  // namespace k4

template <>
struct fmt::formatter<k4::Piece> : ostream_formatter {};

template <>
struct fmt::formatter<k4::Board> : ostream_formatter {};
