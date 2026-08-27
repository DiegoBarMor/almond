#include "event_manager.hpp"

// -----------------------------------------------------------------------------
bool nd::EventManager::handle_event(const std::optional<sf::Event> event) { // FUNC@handle_event
    for (CALLBACK_BOOL callback : __get_callbacks(event)) {
        bool consumed = callback(event);
        if (consumed) return true;
    }
    return false;
} // END@handle_event


// -----------------------------------------------------------------------------
std::vector<CALLBACK_BOOL> nd::EventManager::__get_callbacks(const std::optional<sf::Event> event) { // FUNC@__get_callbacks
    if (event->is<sf::Event::Closed>())                 return _on_closed;
    if (event->is<sf::Event::Resized>())                return _on_resized;
    if (event->is<sf::Event::FocusLost>())              return _on_focus_lost;
    if (event->is<sf::Event::FocusGained>())            return _on_focus_gained;
    if (event->is<sf::Event::MouseEntered>())           return _on_mouse_entered;
    if (event->is<sf::Event::MouseLeft>())              return _on_mouse_left;
    if (event->is<sf::Event::TextEntered>())            return _on_text_entered;
    if (event->is<sf::Event::KeyPressed>())             return _on_key_pressed;
    if (event->is<sf::Event::KeyReleased>())            return _on_key_released;
    if (event->is<sf::Event::MouseWheelScrolled>())     return _on_mouse_wheel_scrolled;
    if (event->is<sf::Event::MouseButtonPressed>())     return _on_mouse_button_pressed;
    if (event->is<sf::Event::MouseButtonReleased>())    return _on_mouse_button_released;
    if (event->is<sf::Event::MouseMoved>())             return _on_mouse_moved;
    if (event->is<sf::Event::JoystickButtonPressed>())  return _on_joystick_button_pressed;
    if (event->is<sf::Event::JoystickButtonReleased>()) return _on_joystick_button_released;
    if (event->is<sf::Event::JoystickMoved>())          return _on_joystick_moved;
    if (event->is<sf::Event::JoystickConnected>())      return _on_joystick_connected;
    if (event->is<sf::Event::JoystickDisconnected>())   return _on_joystick_disconnected;
    if (event->is<sf::Event::TouchBegan>())             return _on_touch_began;
    if (event->is<sf::Event::TouchMoved>())             return _on_touch_moved;
    if (event->is<sf::Event::TouchEnded>())             return _on_touch_ended;
    if (event->is<sf::Event::SensorChanged>())          return _on_sensor_changed;
    return {};
} // END@__get_callbacks


// -----------------------------------------------------------------------------
