#include "behavior.hpp"

// -----------------------------------------------------------------------------
bool nd::Behavior::handle_event(const std::optional<sf::Event> event) { // FUNC@handle_event
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
} // END@handle_event


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_closed(const std::optional<sf::Event> event) { // FUNC@_internal_on_closed
    if (!_on_closed) return false;
    return _on_closed(event);
} // END@_internal_on_closed


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_resized(const std::optional<sf::Event> event) { // FUNC@_internal_on_resized
    if (!_on_resized) return false;
    return _on_resized(event);
} // END@_internal_on_resized


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_focus_lost(const std::optional<sf::Event> event) { // FUNC@_internal_on_focus_lost
    if (!_on_focus_lost) return false;
    return _on_focus_lost(event);
} // END@_internal_on_focus_lost


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_focus_gained(const std::optional<sf::Event> event) { // FUNC@_internal_on_focus_gained
    if (!_on_focus_gained) return false;
    return _on_focus_gained(event);
} // END@_internal_on_focus_gained


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_mouse_entered(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_entered
    if (!_on_mouse_entered) return false;
    return _on_mouse_entered(event);
} // END@_internal_on_mouse_entered


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_mouse_left(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_left
    if (!_on_mouse_left) return false;
    return _on_mouse_left(event);
} // END@_internal_on_mouse_left


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_text_entered(const std::optional<sf::Event> event) { // FUNC@_internal_on_text_entered
    if (!_on_text_entered) return false;
    return _on_text_entered(event);
} // END@_internal_on_text_entered


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_key_pressed(const std::optional<sf::Event> event) { // FUNC@_internal_on_key_pressed
    if (!_on_key_pressed) return false;
    return _on_key_pressed(event);
} // END@_internal_on_key_pressed


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_key_released(const std::optional<sf::Event> event) { // FUNC@_internal_on_key_released
    if (!_on_key_released) return false;
    return _on_key_released(event);
} // END@_internal_on_key_released


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_mouse_wheel_scrolled(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_wheel_scrolled
    if (!_on_mouse_wheel_scrolled) return false;
    return _on_mouse_wheel_scrolled(event);
} // END@_internal_on_mouse_wheel_scrolled


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_mouse_button_pressed(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_button_pressed
    if (!_on_mouse_button_pressed) return false;
    return _on_mouse_button_pressed(event);
} // END@_internal_on_mouse_button_pressed


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_mouse_button_released(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_button_released
    if (!_on_mouse_button_released) return false;
    return _on_mouse_button_released(event);
} // END@_internal_on_mouse_button_released


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_mouse_moved(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_moved
    if (!_on_mouse_moved) return false;
    return _on_mouse_moved(event);
} // END@_internal_on_mouse_moved


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_joystick_button_pressed(const std::optional<sf::Event> event) { // FUNC@_internal_on_joystick_button_pressed
    if (!_on_joystick_button_pressed) return false;
    return _on_joystick_button_pressed(event);
} // END@_internal_on_joystick_button_pressed


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_joystick_button_released(const std::optional<sf::Event> event) { // FUNC@_internal_on_joystick_button_released
    if (!_on_joystick_button_released) return false;
    return _on_joystick_button_released(event);
} // END@_internal_on_joystick_button_released


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_joystick_moved(const std::optional<sf::Event> event) { // FUNC@_internal_on_joystick_moved
    if (!_on_joystick_moved) return false;
    return _on_joystick_moved(event);
} // END@_internal_on_joystick_moved


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_joystick_connected(const std::optional<sf::Event> event) { // FUNC@_internal_on_joystick_connected
    if (!_on_joystick_connected) return false;
    return _on_joystick_connected(event);
} // END@_internal_on_joystick_connected


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_joystick_disconnected(const std::optional<sf::Event> event) { // FUNC@_internal_on_joystick_disconnected
    if (!_on_joystick_disconnected) return false;
    return _on_joystick_disconnected(event);
} // END@_internal_on_joystick_disconnected


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_touch_began(const std::optional<sf::Event> event) { // FUNC@_internal_on_touch_began
    if (!_on_touch_began) return false;
    return _on_touch_began(event);
} // END@_internal_on_touch_began


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_touch_moved(const std::optional<sf::Event> event) { // FUNC@_internal_on_touch_moved
    if (!_on_touch_moved) return false;
    return _on_touch_moved(event);
} // END@_internal_on_touch_moved


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_touch_ended(const std::optional<sf::Event> event) { // FUNC@_internal_on_touch_ended
    if (!_on_touch_ended) return false;
    return _on_touch_ended(event);
} // END@_internal_on_touch_ended


// -----------------------------------------------------------------------------
bool nd::Behavior::_internal_on_sensor_changed(const std::optional<sf::Event> event) { // FUNC@_internal_on_sensor_changed
    if (!_on_sensor_changed) return false;
    return _on_sensor_changed(event);
} // END@_internal_on_sensor_changed


// -----------------------------------------------------------------------------
