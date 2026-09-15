#pragma once
#include "../core/globals.hpp"

namespace nd {
namespace ParserStrings {
    // -------------------------------------------------------------------------
    inline bool str2bool(const std::string& raw_str) {
        return raw_str == "T" || raw_str == "TRUE" || raw_str == "1";
    }


    // -------------------------------------------------------------------------
    inline float str2float(const std::string& raw_str) {
        try {
            return std::stof(raw_str);
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid float string: " << raw_str << std::endl;
            return 0.0f;
        }
    }


    // -------------------------------------------------------------------------
    inline float str2ratio(const std::string& raw_str) {
        return std::min(1.0f, std::max(0.0f, nd::ParserStrings::str2float(raw_str)));
    }


    // -------------------------------------------------------------------------
    inline sf::Color str2color(const std::string& raw_str) {
        size_t pos;
        std::string buffer = raw_str;
        int r = 0, g = 0, b = 0, a = 255;
        for (int i = 0; i < 4; i++) {
            pos = buffer.find(',');
            if (pos == std::string::npos) {
                pos = buffer.size();
            }
            std::string color = buffer.substr(0, pos);
            switch (i) {
                case 0: r = std::stoi(color); break;
                case 1: g = std::stoi(color); break;
                case 2: b = std::stoi(color); break;
                case 3: a = std::stoi(color); break;
            }
            if (pos == buffer.size()) break;
            buffer = buffer.substr(pos + 1);
        }
        return sf::Color(r, g, b, a);
    }


    // -------------------------------------------------------------------------
}
}
