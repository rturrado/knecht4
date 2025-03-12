#pragma once

#include <algorithm>  // binary_search, sort
#include <fmt/ostream.h>
#include <istream>
#include <ostream>
#include <string>  // getline

namespace k4::utils {

// Print a message, read a char from a possible list of options, and repeat until the input is valid
inline char read_char(std::istream& is, std::ostream& os, const std::string& message, std::string options) {
    if (options.empty()) {
        return '\0';
    }

    std::sort(std::begin(options), std::end(options));

    for (;;) {
        fmt::print(os, "{}", message);
        std::string s{};
        std::getline(is, s);
        if (s.size() == 1 && std::binary_search(std::cbegin(options), std::cend(options), s[0])) {
            return s[0];
        }
        fmt::print(os, "\tError: invalid input\n");
    }
}

}  // namespace k4::utils
