#include <fmt/format.h>
#include <ostream>

#include "knecht4/version.hpp"
#include "knecht4/game_manager.hpp"

void print_banner() {
    fmt::print("+-+-+-+-+-+-+-+\n");
    fmt::print("|k|n|e|c|h|t|4|\n");
    fmt::print("+-+-+-+-+-+-+-+\n");
    fmt::print("{} <<>> {}\n", version::get_version(), version::get_release_year());
}

int main() {
    try {
        print_banner();
        k4::GameManager::get_instance().run();
    } catch (const std::runtime_error& error) {
        fmt::print("Error: {}", error.what());
    }
}
