#include "widget.hpp"

// -----------------------------------------------------------------------------
bool nd::Widget::set_spec(std::string key, std::string raw_value) { // FUNC@set_spec
    if (key == "W" || key == "WEIGHT") {
        __weight = nd::ParserStrings::str2float(raw_value);
        return true;
    }
    if (key == "BG" || key == "BG_COLOR") {
        _bg_color = nd::ParserStrings::str2color(raw_value);
        return true;
    }
    return false;
} // END@set_spec


// -----------------------------------------------------------------------------
void nd::Widget::add_child(nd::Widget* child) { // FUNC@add_child
    std::cerr << "Can't add child to non-container widget" << std::endl;
} // END@add_child


// -----------------------------------------------------------------------------
void nd::Widget::build() { // FUNC@build
    _init_shape();
} // END@build


// -----------------------------------------------------------------------------
bool nd::Widget::handle_event(const std::optional<sf::Event> event) { // FUNC@handle_event
    return _internal_handle_event(event);
} // END@handle_event


// -----------------------------------------------------------------------------
void nd::Widget::draw(sf::RenderWindow& window) { // FUNC@draw
    window.draw(_shape);
} // END@draw


// -----------------------------------------------------------------------------
void nd::Widget::set_bg_color(sf::Color color) { // FUNC@set_bg_color
    _bg_color = color;
    _shape.setFillColor(color);
} // END@set_bg_color


// -----------------------------------------------------------------------------
bool nd::Widget::contains_point(sf::Vector2i point) { // FUNC@contains_point
    sf::Vector2f point_f((float)point.x, (float)point.y);
    return _shape.getGlobalBounds().contains(point_f);
} // END@contains_point


// -----------------------------------------------------------------------------
void nd::Widget::force_widget_square() { // FUNC@force_widget_square
    sf::Vector2f size = get_size();
    float short_side = std::min(size.x, size.y);
    sf::Vector2f pos = get_pos();

    if (short_side == size.x) {
        pos.y += (size.y - short_side) / 2.0f;
    } else {
        pos.x += (size.x - short_side) / 2.0f;
    }
    set_pos(pos);
    set_size(sf::Vector2f(short_side, short_side));
} // END@force_widget_square


// -----------------------------------------------------------------------------
void nd::Widget::_init_shape() { // FUNC@_init_shape
    _shape.setSize(_size);
    _shape.setPosition(_pos);
    _shape.setFillColor(get_bg_color());
} // END@_init_shape


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_handle_event(const std::optional<sf::Event> event) { // FUNC@_internal_handle_event
    if (event->is<sf::Event::Closed>())                 return _internal_on_closed(event);
    if (event->is<sf::Event::Resized>())                return _internal_on_resized(event);
    if (event->is<sf::Event::FocusLost>())              return _internal_on_focus_lost(event);
    if (event->is<sf::Event::FocusGained>())            return _internal_on_focus_gained(event);
    if (event->is<sf::Event::MouseEntered>())           return _internal_on_mouse_entered(event);
    if (event->is<sf::Event::MouseLeft>())              return _internal_on_mouse_left(event);
    if (event->is<sf::Event::TextEntered>())            return _internal_on_text_entered(event);
    if (event->is<sf::Event::KeyPressed>())             return _internal_on_key_pressed(event);
    if (event->is<sf::Event::KeyReleased>())            return _internal_on_key_released(event);
    if (event->is<sf::Event::MouseWheelScrolled>())     return _internal_on_mouse_wheel_scrolled(event);
    if (event->is<sf::Event::MouseButtonPressed>())     return _internal_on_mouse_button_pressed(event);
    if (event->is<sf::Event::MouseButtonReleased>())    return _internal_on_mouse_button_released(event);
    if (event->is<sf::Event::MouseMoved>())             return _internal_on_mouse_moved(event);
    if (event->is<sf::Event::JoystickButtonPressed>())  return _internal_on_joystick_button_pressed(event);
    if (event->is<sf::Event::JoystickButtonReleased>()) return _internal_on_joystick_button_released(event);
    if (event->is<sf::Event::JoystickMoved>())          return _internal_on_joystick_moved(event);
    if (event->is<sf::Event::JoystickConnected>())      return _internal_on_joystick_connected(event);
    if (event->is<sf::Event::JoystickDisconnected>())   return _internal_on_joystick_disconnected(event);
    if (event->is<sf::Event::TouchBegan>())             return _internal_on_touch_began(event);
    if (event->is<sf::Event::TouchMoved>())             return _internal_on_touch_moved(event);
    if (event->is<sf::Event::TouchEnded>())             return _internal_on_touch_ended(event);
    if (event->is<sf::Event::SensorChanged>())          return _internal_on_sensor_changed(event);
    return false;
} // END@_internal_handle_event


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_closed(const std::optional<sf::Event> event) { // FUNC@_internal_on_closed
    if (_on_closed) { return _on_closed(event); }
    return false;
} // END@_internal_on_closed


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_resized(const std::optional<sf::Event> event) { // FUNC@_internal_on_resized
    if (_on_resized) { return _on_resized(event); }
    return false;
} // END@_internal_on_resized


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_focus_lost(const std::optional<sf::Event> event) { // FUNC@_internal_on_focus_lost
    if (_on_focus_lost) { return _on_focus_lost(event); }
    return false;
} // END@_internal_on_focus_lost


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_focus_gained(const std::optional<sf::Event> event) { // FUNC@_internal_on_focus_gained
    if (_on_focus_gained) { return _on_focus_gained(event); }
    return false;
} // END@_internal_on_focus_gained


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_mouse_entered(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_entered
    if (_on_mouse_entered) { return _on_mouse_entered(event); }
    return false;
} // END@_internal_on_mouse_entered


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_mouse_left(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_left
    if (_on_mouse_left) { return _on_mouse_left(event); }
    return false;
} // END@_internal_on_mouse_left


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_text_entered(const std::optional<sf::Event> event) { // FUNC@_internal_on_text_entered
    if (_on_text_entered) { return _on_text_entered(event); }
    return false;
} // END@_internal_on_text_entered


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_key_pressed(const std::optional<sf::Event> event) { // FUNC@_internal_on_key_pressed
    if (_on_key_pressed) { return _on_key_pressed(event); }
    return false;
} // END@_internal_on_key_pressed


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_key_released(const std::optional<sf::Event> event) { // FUNC@_internal_on_key_released
    if (_on_key_released) { return _on_key_released(event); }
    return false;
} // END@_internal_on_key_released


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_mouse_wheel_scrolled(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_wheel_scrolled
    if (_on_mouse_wheel_scrolled) { return _on_mouse_wheel_scrolled(event); }
    return false;
} // END@_internal_on_mouse_wheel_scrolled


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_mouse_button_pressed(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_button_pressed
    if (!_on_mouse_button_pressed) return false;
    const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>();
    if (mouseButton && contains_point(mouseButton->position))
        return _on_mouse_button_pressed(event);
    return false;
} // END@_internal_on_mouse_button_pressed


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_mouse_button_released(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_button_released
    if (!_on_mouse_button_released) return false;
    const auto* mouseButton = event->getIf<sf::Event::MouseButtonReleased>();
    if (mouseButton && contains_point(mouseButton->position))
        return _on_mouse_button_released(event);
    return false;
} // END@_internal_on_mouse_button_released


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_mouse_moved(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_moved
    if (!_on_mouse_moved) return false;
    const auto* mouseMove = event->getIf<sf::Event::MouseMoved>();
    if (mouseMove && contains_point(mouseMove->position))
        return _on_mouse_moved(event);
    return false;
} // END@_internal_on_mouse_moved


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_joystick_button_pressed(const std::optional<sf::Event> event) { // FUNC@_internal_on_joystick_button_pressed
    if (_on_joystick_button_pressed) { return _on_joystick_button_pressed(event); }
    return false;
} // END@_internal_on_joystick_button_pressed


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_joystick_button_released(const std::optional<sf::Event> event) { // FUNC@_internal_on_joystick_button_released
    if (_on_joystick_button_released) { return _on_joystick_button_released(event); }
    return false;
} // END@_internal_on_joystick_button_released


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_joystick_moved(const std::optional<sf::Event> event) { // FUNC@_internal_on_joystick_moved
    if (_on_joystick_moved) { return _on_joystick_moved(event); }
    return false;
} // END@_internal_on_joystick_moved


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_joystick_connected(const std::optional<sf::Event> event) { // FUNC@_internal_on_joystick_connected
    if (_on_joystick_connected) { return _on_joystick_connected(event); }
    return false;
} // END@_internal_on_joystick_connected


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_joystick_disconnected(const std::optional<sf::Event> event) { // FUNC@_internal_on_joystick_disconnected
    if (_on_joystick_disconnected) { return _on_joystick_disconnected(event); }
    return false;
} // END@_internal_on_joystick_disconnected


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_touch_began(const std::optional<sf::Event> event) { // FUNC@_internal_on_touch_began
    if (_on_touch_began) { return _on_touch_began(event); }
    return false;
} // END@_internal_on_touch_began


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_touch_moved(const std::optional<sf::Event> event) { // FUNC@_internal_on_touch_moved
    if (_on_touch_moved) { return _on_touch_moved(event); }
    return false;
} // END@_internal_on_touch_moved


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_touch_ended(const std::optional<sf::Event> event) { // FUNC@_internal_on_touch_ended
    if (_on_touch_ended) { return _on_touch_ended(event); }
    return false;
} // END@_internal_on_touch_ended


// -----------------------------------------------------------------------------
bool nd::Widget::_internal_on_sensor_changed(const std::optional<sf::Event> event) { // FUNC@_internal_on_sensor_changed
    if (_on_sensor_changed) { return _on_sensor_changed(event); }
    return false;
} // END@_internal_on_sensor_changed


// -----------------------------------------------------------------------------
