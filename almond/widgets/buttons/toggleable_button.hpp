#pragma once
#include "button_primitive.hpp"

namespace nd {
class ToggleableButton : public ButtonPrimitive {
public:
    bool set_spec(std::string key, std::string raw_value) override; // HEAD@set_spec
    void build() override; // HEAD@build
    bool handle_event(const std::optional<sf::Event> event) override; // HEAD@handle_event
    void draw(sf::RenderWindow& window) override; // HEAD@draw

    void      set_checked          (bool checked)    { _checked = checked;             }
    void      set_color_mark       (sf::Color color) { _color_mark = color;            }
    void      set_outline_thickness(float thickness) { _outline_thickness = thickness; }
    bool      get_checked          () { return _checked;           }
    sf::Color get_color_mark       () { return _color_mark;        }
    float     get_outline_thickness() { return _outline_thickness; }

    virtual void link_on_toggle(CALLBACK_VOID callback) { _on_toggle = callback; }

protected:
    ToggleableButton() : ButtonPrimitive() {}

    virtual void _internal_on_toggle() {};

    bool _checked = false;
    sf::Color _color_mark = sf::Color(0,0,200,200);
    float _outline_thickness = 0.2f; // ratio (0.0f-1.0f) [WIP]

    CALLBACK_VOID _on_toggle;

    sf::Color _color_overlay = sf::Color(255, 255, 255, 128);
    sf::RectangleShape _shape_overlay = sf::RectangleShape();
};
}
