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
bool nd::ButtonPrimitive::handle_event(nd::Event event) { // FUNC@handle_event
    if (_state == State::DISABLED) return false;

    bool consumed = false;
    switch (event.none.type) {
        case nd::EventType::MOUSE_BUTTON_PRESSED:
            consumed = _on_mouse_button_pressed(event); break;
        case nd::EventType::MOUSE_BUTTON_RELEASED:
            consumed = _on_mouse_button_released(event); break;
        case nd::EventType::MOUSE_MOVED:
            consumed = _on_mouse_moved(event); break;
        default: break;
    }
    if (consumed) return true;

    return nd::Widget::handle_event(event);
} // END@handle_event


// -----------------------------------------------------------------------------
void nd::ButtonPrimitive::set_enabled(bool enabled) { // FUNC@set_enabled
    __set_state(enabled ? State::IDLE : State::DISABLED);
} // END@set_enabled


// -----------------------------------------------------------------------------
bool nd::ButtonPrimitive::get_enabled() { // FUNC@get_enabled
    return _state != State::DISABLED;
} // END@get_enabled


// -----------------------------------------------------------------------------
bool nd::ButtonPrimitive::_on_mouse_button_pressed(nd::Event event) { // FUNC@_on_mouse_button_pressed
    if (!contains_point(event.mouse_button_pressed.position)) return false;
    __set_state(State::PRESSED);

    return _on_click ? _on_click(event) : false;
} // END@_on_mouse_button_pressed


// -----------------------------------------------------------------------------
bool nd::ButtonPrimitive::_on_mouse_button_released(nd::Event event) { // FUNC@_on_mouse_button_released
    if (contains_point(event.mouse_button_released.position)) {
        __set_state(State::HOVER);
    }
    else if (_state == State::PRESSED) {
        __set_state(State::IDLE);
    }
    return false;
} // END@_on_mouse_button_released


// -----------------------------------------------------------------------------
bool nd::ButtonPrimitive::_on_mouse_moved(nd::Event event) { // FUNC@_on_mouse_moved
    if (contains_point(event.mouse_moved.position)) {
        if (_state == State::IDLE) {
            __set_state(State::HOVER);
        }
    }
    else if (_state == State::HOVER) {
        __set_state(State::IDLE);
    }
    return false;
} // END@_on_mouse_moved


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
