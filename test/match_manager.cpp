#include "knecht4/match_manager.hpp"

#include <gmock/gmock.h>  // ThrowsMessage
#include <gtest/gtest.h>
#include <sstream>

namespace k4 {

TEST(match_manager, query_turn_user) {
    std::istringstream iss{"u\n"};
    std::ostringstream oss{};
    MatchManager &match_manager = MatchManager::get_instance(iss, oss);
    match_manager.query_turn();
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("User starts with '+' pieces"));
}

TEST(match_manager, query_turn_machine) {
    std::istringstream iss{ "m\n" };
    std::ostringstream oss{};
    MatchManager &match_manager = MatchManager::get_instance(iss, oss);
    match_manager.query_turn();
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Machine starts with '+' pieces"));
}

TEST(match_manager, run_draw) {
    std::istringstream iss{ "6\n" };
    std::ostringstream oss{};
    MatchManager &match_manager = MatchManager::get_instance(iss, oss);
    Board board_almost_full{
        "ryryr r"
        "yryryry"
        "rryyyrr"
        "yyrrryy"
        "rryyyrr"
        "yyrrryy"
    };
    match_manager.set_board(std::make_unique<Board>(board_almost_full));
    match_manager.set_turn(Turn::user);
    match_manager.run();
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("End of game: draw!"));
}

}  // namespace k4
