#pragma once
#include "text.hpp"

namespace nd {
class TextInput : public Text {
public:
    TextInput(sf::Font font) : Text(font) {
        _font_color = sf::Color::Black;
        set_bg_color(sf::Color(0x4A4A4AFF));
    }
    std::unique_ptr<Widget> clone() const override {
        return std::make_unique<TextInput>(font);
    }

    bool set_spec(std::string key, std::string raw_value) override; // HEAD@set_spec
    void build() override; // HEAD@build
    bool handle_event(const nd::Event& event) override; // HEAD@handle_event
    void draw(sf::RenderWindow& window) override; // HEAD@draw

    void set_hint_str  (const std::string& hint) { __hint_str = hint;    }
    void set_hint_color(const sf::Color& color)  { __hint_color = color; }

    const std::string& get_hint_str  () const { return __hint_str;   }
    const sf::Color&   get_hint_color() const { return __hint_color; }

protected:
    float _outline_thickness = 0.1f; // ratio (0.0f-1.0f) [WIP]
    bool _on_mouse_button_pressed(const nd::Event& event); // HEAD@_on_mouse_button_pressed
    bool _on_text_entered(const nd::Event& event); // HEAD@_on_text_entered

private:
    std::string __hint_str = "";
    bool __is_focused = false;

    sf::Color __hint_color = sf::Color(100, 100, 100, 255);
    sf::Color __color_overlay_idle = sf::Color(200, 200, 200, 200);
    sf::Color __color_overlay_focused = sf::Color(255, 255, 255, 200);
    sf::RectangleShape __shape_overlay = sf::RectangleShape();
};
}
