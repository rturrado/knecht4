#include "knecht4/board.hpp"

#include <gmock/gmock.h>  // ThrowsMessage
#include <gtest/gtest.h>

namespace k4 {

class BoardTest : public ::testing::Test {
protected:
    void SetUp() override {}

    Board board_empty{};
    Board board_full{
        "ryryryr"
        "yryryry"
        "rryyyrr"
        "yyrrryy"
        "rryyyrr"
        "yyrrryy"
    };
    Board board_vertical_yellow_line{
        "       "
        "       "
        "rr y   "
        "yyryryy"
        "rryyyrr"
        "yyryryy"
    };
    Board board_horizontal_yellow_line{
        "       "
        "       "
        "rr     "
        "yyryyyy"
        "rryyyrr"
        "yyryryy"
    };
    Board board_top_down_yellow_line{
        "       "
        "       "
        "rry    "
        "yyryryy"
        "rryyyrr"
        "yyrrryy"
    };
    Board board_bottom_up_yellow_line{
        "       "
        "       "
        "rr  y  "
        "yyryryy"
        "rryyyrr"
        "yyrrryy"
    };
};

TEST_F(BoardTest, constructor_default) {
    for (RowIndex i = 0; i < number_of_rows; ++i) {
        for (ColumnIndex j = 0; j < number_of_columns; ++j) {
            EXPECT_EQ(board_empty.get_cell(i, j), std::nullopt);
        }
    }
}

TEST_F(BoardTest, constructor_string) {
    EXPECT_EQ(board_full.get_cell(0, 0), Piece::red);
    EXPECT_EQ(board_full.get_cell(3, 3), Piece::red);
    EXPECT_EQ(board_full.get_cell(5, 6), Piece::yellow);
}

TEST_F(BoardTest, insert) {
    auto row_index = board_empty.insert(1, Piece::red);
    EXPECT_EQ(row_index, bottom_row_index);
    EXPECT_THAT([this]() { [[maybe_unused]] auto row_index = board_full.insert(1, Piece::red); },
        ::testing::ThrowsMessage<std::runtime_error>("trying to insert in a full column: 1"));
}

TEST_F(BoardTest, check) {
    EXPECT_EQ(board_full.check(CellIndex{ 0, 6 }), std::nullopt);
    auto vertical_yellow_line = Line{ CellIndex{ 2, 3 }, CellIndex{ 5, 3 }};
    auto horizontal_yellow_line = Line{ CellIndex{ 3, 3 }, CellIndex{ 3, 6 }};
    auto top_down_yellow_line = Line{ CellIndex{ 2, 2 }, CellIndex{ 5, 5 }};
    auto bottom_up_yellow_line = Line{ CellIndex{ 5, 1 }, CellIndex{ 2, 4 }};
    EXPECT_EQ(board_vertical_yellow_line.check(CellIndex{ 2, 3 }), vertical_yellow_line);
    EXPECT_EQ(board_horizontal_yellow_line.check(CellIndex{ 3, 6 }), horizontal_yellow_line);
    EXPECT_EQ(board_top_down_yellow_line.check(CellIndex{ 2, 2 }), top_down_yellow_line);
    EXPECT_EQ(board_bottom_up_yellow_line.check(CellIndex{ 2, 4 }), bottom_up_yellow_line);
}

TEST_F(BoardTest, get_cell) {
    EXPECT_EQ(board_empty.get_cell(0, 0), std::nullopt);
    EXPECT_EQ(board_full.get_cell(0, 6), Piece::red);
}

TEST_F(BoardTest, full_column) {
    EXPECT_EQ(board_empty.full_column(0), false);
    EXPECT_EQ(board_full.full_column(0), true);
}

TEST_F(BoardTest, full) {
    EXPECT_EQ(board_empty.full(), false);
    EXPECT_EQ(board_full.full(), true);
}

}  // namespace k4
