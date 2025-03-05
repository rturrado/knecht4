#pragma once

#include <algorithm>  // binary_search, sort
#include <iostream>  // cin
#include <fmt/core.h>
#include <string>  // getline

namespace k4::utils {

// Print a message, read a char from a possible list of options, and repeat until the input is valid
inline char read_char(const std::string& message, std::string options) {
    if (options.empty()) {
        return '\0';
    }

    std::sort(std::begin(options), std::end(options));

    for (;;) {
        fmt::print("{}", message);
        std::string s{};
        std::getline(std::cin, s);
        if (s.size() == 1 && std::binary_search(std::cbegin(options), std::cend(options), s[0])) {
            return s[0];
        }
        fmt::print("\tError: invalid input\n");
    }
}

}  // namespace k4::utils
