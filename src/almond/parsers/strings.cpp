#include "strings.hpp"

bool nd::parse_bool_string(std::string raw_str) {
    return raw_str == "T" || raw_str == "TRUE" || raw_str == "1";
}

float nd::parse_float_string(std::string raw_str) {
    try {
        return std::stof(raw_str);
    } catch (const std::invalid_argument&) {
        std::cout << "Invalid float string: " << raw_str << std::endl;
        return 0.0f;
    }
}

float nd::parse_ratio_string(std::string raw_str) {
    return std::min(1.0f, std::max(0.0f, nd::parse_float_string(raw_str)));
}

sf::Color nd::parse_color_string(std::string raw_str) {
    size_t pos;
    int r = 0, g = 0, b = 0, a = 255;
    for (int i = 0; i < 4; i++) {
        pos = raw_str.find(',');
        if (pos == std::string::npos) {
            pos = raw_str.size();
        }
        std::string color = raw_str.substr(0, pos);
        switch (i) {
            case 0: r = std::stoi(color); break;
            case 1: g = std::stoi(color); break;
            case 2: b = std::stoi(color); break;
            case 3: a = std::stoi(color); break;
        }
        if (pos == raw_str.size()) break;
        raw_str = raw_str.substr(pos + 1);
    }
    return sf::Color(r, g, b, a);
}
