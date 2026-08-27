#include "event_manager.hpp"

// -----------------------------------------------------------------------------
bool nd::EventManager::key_pressed_is(sf::Keyboard::Key key) { // FUNC@key_pressed_is
    const auto key_pressed = nd::EventManager::get_key_pressed();
    if (!key_pressed) return false;
    return key_pressed->code == key;
} // END@key_pressed_is


// -----------------------------------------------------------------------------
bool nd::EventManager::key_released_is(sf::Keyboard::Key key) { // FUNC@key_released_is
    const auto key_released = nd::EventManager::get_key_pressed();
    if (!key_released) return false;
    return key_released->code == key;
} // END@key_released_is


// -----------------------------------------------------------------------------
bool nd::EventManager::handle_event(const std::optional<sf::Event> event) { // FUNC@handle_event
    __last_event = event;
    __last_mouse_pos = __get_last_mouse_pos();
    for (CALLBACK_BOOL callback : __get_callbacks()) {
        bool consumed = callback();
        if (consumed) return true;
    }
    return false;
} // END@handle_event


// -----------------------------------------------------------------------------
std::vector<CALLBACK_BOOL> nd::EventManager::__get_callbacks() { // FUNC@__get_callbacks
    if (__last_event->is<sf::Event::Closed>())                 return _on_closed;
    if (__last_event->is<sf::Event::Resized>())                return _on_resized;
    if (__last_event->is<sf::Event::FocusLost>())              return _on_focus_lost;
    if (__last_event->is<sf::Event::FocusGained>())            return _on_focus_gained;
    if (__last_event->is<sf::Event::MouseEntered>())           return _on_mouse_entered;
    if (__last_event->is<sf::Event::MouseLeft>())              return _on_mouse_left;
    if (__last_event->is<sf::Event::TextEntered>())            return _on_text_entered;
    if (__last_event->is<sf::Event::KeyPressed>())             return _on_key_pressed;
    if (__last_event->is<sf::Event::KeyReleased>())            return _on_key_released;
    if (__last_event->is<sf::Event::MouseWheelScrolled>())     return _on_mouse_wheel_scrolled;
    if (__last_event->is<sf::Event::MouseButtonPressed>())     return _on_mouse_button_pressed;
    if (__last_event->is<sf::Event::MouseButtonReleased>())    return _on_mouse_button_released;
    if (__last_event->is<sf::Event::MouseMoved>())             return _on_mouse_moved;
    if (__last_event->is<sf::Event::JoystickButtonPressed>())  return _on_joystick_button_pressed;
    if (__last_event->is<sf::Event::JoystickButtonReleased>()) return _on_joystick_button_released;
    if (__last_event->is<sf::Event::JoystickMoved>())          return _on_joystick_moved;
    if (__last_event->is<sf::Event::JoystickConnected>())      return _on_joystick_connected;
    if (__last_event->is<sf::Event::JoystickDisconnected>())   return _on_joystick_disconnected;
    if (__last_event->is<sf::Event::TouchBegan>())             return _on_touch_began;
    if (__last_event->is<sf::Event::TouchMoved>())             return _on_touch_moved;
    if (__last_event->is<sf::Event::TouchEnded>())             return _on_touch_ended;
    if (__last_event->is<sf::Event::SensorChanged>())          return _on_sensor_changed;
    return {};
} // END@__get_callbacks


// -----------------------------------------------------------------------------
sf::Vector2i nd::EventManager::__get_last_mouse_pos() { // FUNC@__get_last_mouse_pos
    const auto mouse_moved = __last_event->getIf<sf::Event::MouseMoved>();
    if (mouse_moved) return mouse_moved->position;

    const auto mouse_button_pressed = __last_event->getIf<sf::Event::MouseButtonPressed>();
    if (mouse_button_pressed) return mouse_button_pressed->position;

    const auto mouse_button_released = __last_event->getIf<sf::Event::MouseButtonReleased>();
    if (mouse_button_released) return mouse_button_released->position;

    const auto mouse_wheel_scrolled = __last_event->getIf<sf::Event::MouseWheelScrolled>();
    if (mouse_wheel_scrolled) return mouse_wheel_scrolled->position;

    return __last_mouse_pos;
} // END@__get_last_mouse_pos


// -----------------------------------------------------------------------------
