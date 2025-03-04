#include <fmt/format.h>

#include "knecht4/version.hpp"

void print_banner() {
    fmt::print("+-+-+-+-+-+-+-+\n");
    fmt::print("|k|n|e|c|h|t|4|\n");
    fmt::print("+-+-+-+-+-+-+-+\n");
    fmt::print("{} <<>> {}\n", version::get_version(), version::get_release_year());
}

int main(int argc, const char** argv) {
    print_banner();
}
