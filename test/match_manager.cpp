#include "knecht4/match_manager.hpp"

#include <gmock/gmock.h>  // ThrowsMessage
#include <gtest/gtest.h>
#include <sstream>

namespace k4 {

class MatchManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        oss.str("");
        oss.clear();
    }

    std::istringstream iss_user_starts{ "u\n" };
    std::istringstream iss_machine_starts{ "m\n" };
    std::istringstream iss_user_chooses_column{ "6\n" };
    std::ostringstream oss{};
    Board board_almost_full{
        "ryryr r"
        "yryryry"
        "rryyyrr"
        "yyrrryy"
        "rryyyrr"
        "yyrrryy"
    };
};

TEST_F(MatchManagerTest, query_turn_user_starts) {
    auto& match_manager = MatchManager::get_instance(iss_user_starts, oss);
    match_manager.query_turn();
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("User starts with '+' pieces"));
}

TEST_F(MatchManagerTest, run_draw) {
    auto& match_manager = MatchManager::get_instance(iss_user_chooses_column, oss);
    match_manager.set_board(std::make_unique<Board>(board_almost_full));
    match_manager.set_turn(Turn::user);
    match_manager.run();
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("End of game: draw!"));
}

}  // namespace k4
