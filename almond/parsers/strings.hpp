#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

namespace nd {

bool parse_bool_string(std::string raw_str);
float parse_float_string(std::string raw_str);
float parse_ratio_string(std::string raw_str);
sf::Color parse_color_string(std::string raw_str);

}
