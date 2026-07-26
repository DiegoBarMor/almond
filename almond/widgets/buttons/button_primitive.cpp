#include "button_primitive.hpp"

// -----------------------------------------------------------------------------
bool nd::ButtonPrimitive::set_spec(std::string key, std::string raw_value) { // FUNC@set_spec
    if (key == "E" || key == "ENABLED") {
        set_enabled(nd::ParserStrings::str2bool(raw_value));
        return true;
    }
    if (key == "BGI" || key == "BG_IDLE") {
        __bg_idle = nd::ParserStrings::str2color(raw_value);
        return true;
    }
    if (key == "BGH" || key == "BG_HOVER") {
        __bg_hover = nd::ParserStrings::str2color(raw_value);
        return true;
    }
    if (key == "BGP" || key == "BG_PRESSED") {
        __bg_pressed = nd::ParserStrings::str2color(raw_value);
        return true;
    }
    if (key == "BGD" || key == "BG_DISABLED") {
        __bg_disabled = nd::ParserStrings::str2color(raw_value);
        return true;
    }
    return nd::Widget::set_spec(key, raw_value);
} // END@set_spec


// -----------------------------------------------------------------------------
void nd::ButtonPrimitive::build() { // FUNC@build
    __set_state(_state); // this ensures that the proper colors are being used
    nd::Widget::build();
} // END@build


// -----------------------------------------------------------------------------
void nd::ButtonPrimitive::set_enabled(bool enabled) { // FUNC@set_enabled
    __set_state(enabled ? State::IDLE : State::DISABLED);
} // END@set_enabled


// -----------------------------------------------------------------------------
bool nd::ButtonPrimitive::get_enabled() { // FUNC@get_enabled
    return _state != State::DISABLED;
} // END@get_enabled


// -----------------------------------------------------------------------------
bool nd::ButtonPrimitive::_internal_on_mouse_click(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_click
    if (_state == State::DISABLED) return false;
    if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (!INTERSECTS_MOUSE(mouseButton->position)) return false;
    }
    __set_state(State::PRESSED);
    if (!_on_mouse_click) return false;
    return _on_mouse_click(event);
} // END@_internal_on_mouse_click


// -----------------------------------------------------------------------------
bool nd::ButtonPrimitive::_internal_on_mouse_release(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_release
    if (_state == State::DISABLED) return false;
    if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonReleased>()) {
        if (INTERSECTS_MOUSE(mouseButton->position)) {
            // update the button state and carry out _on_mouse_release as usual
            __set_state(State::HOVER);
            if (!_on_mouse_release) return false;
            return _on_mouse_release(event);
        }
    }
    if (_state == State::PRESSED) {
        // mouse was pressed on the button but released outside its bounds
        // the button state is updated, but _on_mouse_release is not called
        // basically, the on_release action is cancelled
        __set_state(State::IDLE);
    }
    return false;
} // END@_internal_on_mouse_release


// -----------------------------------------------------------------------------
bool nd::ButtonPrimitive::_internal_on_mouse_move(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_move
    if (_state == State::DISABLED) return false;
    if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>()) {
        if (INTERSECTS_MOUSE(mouseMove->position)) {
            if (_state == State::IDLE) {
                __set_state(State::HOVER);
            }
            if (!_on_mouse_move) return false;
            return _on_mouse_move(event);
        }
    }
    if (_state == State::HOVER) {
        __set_state(State::IDLE);
    }
    return false;
} // END@_internal_on_mouse_move


// -----------------------------------------------------------------------------
void nd::ButtonPrimitive::__set_state(State state) { // FUNC@__set_state
    _state = state;
    switch (state) {
        case State::IDLE:
            _bg_color = __bg_idle; break;
        case State::HOVER:
            _bg_color = __bg_hover; break;
        case State::PRESSED:
            _bg_color = __bg_pressed; break;
        case State::DISABLED:
            _bg_color = __bg_disabled; break;
    }
    _shape.setFillColor(_bg_color);
} // END@__set_state


// -----------------------------------------------------------------------------
