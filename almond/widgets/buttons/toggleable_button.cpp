#include "toggleable_button.hpp"

// -----------------------------------------------------------------------------
bool nd::ToggleableButton::set_spec(std::string key, std::string raw_value) { // FUNC@set_spec
    if (key == "CHK" || key == "CHECKED") {
        set_checked(nd::ParserStrings::str2bool(raw_value));
        return true;
    }
    if (key == "FGM" || key == "COLOR_MARK") {
        _color_mark = nd::ParserStrings::str2color(raw_value);
        return true;
    }
    if (key == "OTH" || key == "OUTLINE_THICKNESS") {
        _outline_thickness = nd::ParserStrings::str2ratio(raw_value);
        return true;
    }
    return nd::ButtonPrimitive::set_spec(key, raw_value);
} // END@set_spec


// -----------------------------------------------------------------------------
void nd::ToggleableButton::build() { // FUNC@build
    set_checked(_checked);
    force_widget_square();
    nd::ButtonPrimitive::build();

    sf::Vector2f
        size = (1.0f-_outline_thickness)*_size,
        pos = _pos + (_outline_thickness/2.0f)*_size;
    _shape_overlay.setSize(size);
    _shape_overlay.setPosition(pos);
    _shape_overlay.setFillColor(_color_overlay);
} // END@build


// -----------------------------------------------------------------------------
void nd::ToggleableButton::draw(sf::RenderWindow& window) { // FUNC@draw
    nd::ButtonPrimitive::draw(window);
    window.draw(_shape_overlay);
} // END@draw


// -----------------------------------------------------------------------------
bool nd::ToggleableButton::_on_mouse_button_released(nd::Event event) { // FUNC@_on_mouse_button_released
    if (_state == State::DISABLED) return false;

    if (contains_point(event.mouse_button_released.position)) {
        set_checked(!_checked);
        if (_on_toggle) {
            bool consumed = _on_toggle(event);
            if (consumed) return true;
        }
    }
    return nd::ButtonPrimitive::_on_mouse_button_released(event);
} // END@_on_mouse_button_released


// -----------------------------------------------------------------------------
