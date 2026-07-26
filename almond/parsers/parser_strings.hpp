#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

namespace nd {
namespace ParserStrings {
    bool str2bool(std::string raw_str); // HEAD@str2bool
    float str2float(std::string raw_str); // HEAD@str2float
    float str2ratio(std::string raw_str); // HEAD@str2ratio
    sf::Color str2color(std::string raw_str); // HEAD@str2color
}
}
