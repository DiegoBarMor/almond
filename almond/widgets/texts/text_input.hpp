#pragma once
#include "text.hpp"

namespace nd {
////////////////////////////////////////////////////////////////////////////////

class TextInput : public Text {
public:
    TextInput(sf::Font font); // HEAD@TextInput
    TextInput* clone() override { return new TextInput(font); }

    bool set_spec(std::string key, std::string raw_value) override; // HEAD@set_spec
    void build() override; // HEAD@build
    void draw(sf::RenderWindow& window) override; // HEAD@draw

    void        set_hint_str  (std::string hint) { __hint_str = hint;    }
    void        set_hint_color(sf::Color color)  { __hint_color = color; }
    std::string get_hint_str  ()                 { return __hint_str;    }
    sf::Color   get_hint_color()                 { return __hint_color;  }

protected:
    bool _internal_on_mouse_release(const std::optional<sf::Event> event) override; // HEAD@_internal_on_mouse_release
    bool _internal_on_text_entered (const std::optional<sf::Event> event) override; // HEAD@_internal_on_text_entered

    float _outline_thickness = 0.1f; // ratio (0.0f-1.0f) [WIP]

private:
    std::string __hint_str = "";
    bool __is_focused = false;

    sf::Color __hint_color = sf::Color(100, 100, 100, 255);
    sf::Color __color_overlay_idle = sf::Color(200, 200, 200, 200);
    sf::Color __color_overlay_focused = sf::Color(255, 255, 255, 200);
    sf::RectangleShape __shape_overlay = sf::RectangleShape();
};
}
