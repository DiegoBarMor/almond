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
bool nd::ToggleableButton::handle_event(const std::optional<sf::Event> event) { // FUNC@handle_event
    if (_state == State::DISABLED) return false;
    if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonReleased>()) {
        if (
            event->is<sf::Event::MouseButtonReleased>() &&
            INTERSECTS_MOUSE(mouseButton->position)
        )
            _internal_on_toggle();
    }
    return nd::ButtonPrimitive::handle_event(event);
} // END@handle_event


// -----------------------------------------------------------------------------
void nd::ToggleableButton::draw(sf::RenderWindow& window) { // FUNC@draw
    nd::ButtonPrimitive::draw(window);
    window.draw(_shape_overlay);
} // END@draw


// -----------------------------------------------------------------------------
