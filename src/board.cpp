#include "knecht4/board.hpp"

#include <fmt/format.h>

namespace k4 {

std::ostream& operator<<(std::ostream& os, const Piece& piece) {
    return os << (piece == Piece::red ? "+" : "-");
}

Board::Board()
: next_piece_{ Piece::red } {}

void Board::reset() {
    std::for_each(data_.begin(), data_.end(), [](auto& column) {
        column.fill(std::nullopt);
    });
    next_piece_ = Piece::red;
}

void Board::print() const {
    fmt::print("{}", *this);
}

[[nodiscard]] RowIndex Board::insert(ColumnIndex column_index) {
    assert(column_index < number_of_columns);
    if (auto number_of_empty_rows = get_number_of_empty_rows(column_index)) {
        auto row_index = RowIndex{ static_cast<RowIndex>(number_of_empty_rows - 1) };
        data_[row_index][column_index] = next_piece_;
        next_piece_ = next_piece_ == Piece::red ? Piece::yellow : Piece::red;
        return row_index;
    } else {
        throw BoardError{ fmt::format("trying to insert in a full column: {}", column_index) };
    }
}

[[nodiscard]] std::optional<Line> Board::check_vertical(const CellIndex& cell_index) const {
    auto row_index = cell_index.row;
    auto column_index = cell_index.column;
    const auto& piece = data_[row_index][column_index];
    int pieces_above = 0;
    auto start_row = RowIndex{ row_index };
    for (int i = row_index - 1; i >= 0 && data_[i][column_index] == piece; --i) {
        start_row = i;
        pieces_above++;
    }
    int pieces_below = 0;
    auto end_row = RowIndex{ row_index };
    for (int i = row_index + 1; i < number_of_rows && data_[i][column_index] == piece; ++i) {
        end_row = i;
        pieces_below++;
    }
    if (pieces_above + pieces_below + 1 >= minimum_line_size) {
        return Line{ CellIndex{ start_row, column_index }, CellIndex{ end_row, column_index } };
    }
    return std::nullopt;
}

[[nodiscard]] std::optional<Line> Board::check_horizontal(const CellIndex& cell_index) const {
    auto row_index = cell_index.row;
    auto column_index = cell_index.column;
    const auto& piece = data_[row_index][column_index];
    int pieces_left = 0;
    auto start_column = ColumnIndex{ column_index };
    for (int j = column_index - 1; j >= 0 && data_[row_index][j] == piece; --j) {
        start_column = j;
        pieces_left++;
    }
    int pieces_right = 0;
    auto end_column = ColumnIndex{ column_index };
    for (int j = column_index + 1; j < number_of_columns && data_[row_index][j] == piece; ++j) {
        end_column = j;
        pieces_right++;
    }
    if (pieces_left + pieces_right + 1 >= minimum_line_size) {
        return Line{ CellIndex{ row_index, start_column }, CellIndex{ row_index, end_column } };
    }
    return std::nullopt;
}

[[nodiscard]] std::optional<Line> Board::check_diagonal_top_down(const CellIndex& cell_index) const {
    auto row_index = cell_index.row;
    auto column_index = cell_index.column;
    const auto& piece = data_[row_index][column_index];
    int pieces_top = 0;
    auto start_row = RowIndex{ row_index };
    auto start_column = ColumnIndex{ column_index };
    for (int i = row_index - 1, j = column_index - 1; i >=0 && j >= 0 && data_[i][j] == piece; --i, --j) {
        start_row = i;
        start_column = j;
        pieces_top++;
    }
    int pieces_down = 0;
    auto end_row = RowIndex{ row_index };
    auto end_column = ColumnIndex{ column_index };
    for (int i = row_index + 1, j = column_index + 1; i < number_of_rows && j < number_of_columns && data_[i][j] == piece; ++i, ++j) {
        end_row = i;
        end_column = j;
        pieces_down++;
    }
    if (pieces_top + pieces_down + 1 >= minimum_line_size) {
        return Line{ CellIndex{ start_row, start_column }, CellIndex{ end_row, end_column } };
    }
    return std::nullopt;
}

[[nodiscard]] std::optional<Line> Board::check_diagonal_bottom_up(const CellIndex& cell_index) const {
    auto row_index = cell_index.row;
    auto column_index = cell_index.column;
    const auto& piece = data_[row_index][column_index];
    int pieces_bottom = 0;
    auto start_row = RowIndex{ row_index };
    auto start_column = ColumnIndex{ column_index };
    for (int i = row_index + 1, j = column_index - 1; i < number_of_rows && j >= 0 && data_[i][j] == piece; ++i, --j) {
        start_row = i;
        start_column = j;
        pieces_bottom++;
    }
    int pieces_up = 0;
    auto end_row = RowIndex{ row_index };
    auto end_column = ColumnIndex{ column_index };
    for (int i = row_index - 1, j = column_index + 1; i >= 0 && j < number_of_columns && data_[i][j] == piece; --i, ++j) {
        end_row = i;
        end_column = j;
        pieces_up++;
    }
    if (pieces_bottom + pieces_up + 1 >= minimum_line_size) {
        return Line{ CellIndex{ start_row, start_column }, CellIndex{ end_row, end_column } };
    }
    return std::nullopt;
}

[[nodiscard]] std::optional<Line> Board::check_diagonal(const CellIndex& cell_index) const {
    if (auto line = check_diagonal_bottom_up(cell_index); line) {
        return line;
    }
    return check_diagonal_top_down(cell_index);
}

[[nodiscard]] std::optional<Line> Board::check(const CellIndex& cell_index) const {
    if (auto line = check_vertical(cell_index); line) {
        return line;
    }
    if (auto line = check_horizontal(cell_index); line) {
        return line;
    }
    return check_diagonal(cell_index);
}

[[nodiscard]] Board::Cell Board::get_cell(std::uint8_t row_index, std::uint8_t column_index) const {
    assert(row_index < number_of_rows);
    assert(row_index < number_of_columns);
    return data_[row_index][column_index];
}

[[nodiscard]] Piece Board::get_next_piece() const {
    return next_piece_;
}

[[nodiscard]] std::uint8_t Board::get_number_of_empty_rows(ColumnIndex column_index) const {
    assert(column_index < number_of_columns);
    return std::count_if(data_.begin(), data_.end(),
        [&column_index](const auto& row) {
            return !row[column_index].has_value();
        });
}

[[nodiscard]] bool Board::full_column(ColumnIndex column_index) const {
    const auto& top_row = data_[0];
    return top_row[column_index].has_value();
}

[[nodiscard]] bool Board::full() const {
    const auto& top_row = data_[0];
    return std::all_of(top_row.begin(), top_row.end(),
        [](const auto& cell) {
            return cell.has_value();
    });
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    os << "|1|2|3|4|5|6|7|\n";
    for (std::uint8_t i = 0; i < number_of_rows; ++i) {
        for (std::uint8_t j = 0; j < number_of_columns; ++j) {
            auto cell = board.get_cell(i, j);
            os << "|";
            os << (!cell.has_value() ? " " : cell.value() == Piece::red ? "+" : "-");
        }
        os << "|\n";
    }
    return os;
}

}  // namespace board
