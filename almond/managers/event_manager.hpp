#pragma once
#include "../core/globals.hpp"

namespace nd {
class EventManager {
public:
    EventManager() {};

    #define ADD_CALLBACK(event_name) \
        inline void add_on_##event_name(CALLBACK_BOOL callback) { _on_##event_name.push_back(callback); }
    ADD_CALLBACK(closed)
    ADD_CALLBACK(resized)
    ADD_CALLBACK(focus_lost)
    ADD_CALLBACK(focus_gained)
    ADD_CALLBACK(mouse_entered)
    ADD_CALLBACK(mouse_left)
    ADD_CALLBACK(text_entered)
    ADD_CALLBACK(key_pressed)
    ADD_CALLBACK(key_released)
    ADD_CALLBACK(mouse_wheel_scrolled)
    ADD_CALLBACK(mouse_button_pressed)
    ADD_CALLBACK(mouse_button_released)
    ADD_CALLBACK(mouse_moved)
    ADD_CALLBACK(joystick_button_pressed)
    ADD_CALLBACK(joystick_button_released)
    ADD_CALLBACK(joystick_moved)
    ADD_CALLBACK(joystick_connected)
    ADD_CALLBACK(joystick_disconnected)
    ADD_CALLBACK(touch_began)
    ADD_CALLBACK(touch_moved)
    ADD_CALLBACK(touch_ended)
    ADD_CALLBACK(sensor_changed)
    #undef ADD_CALLBACK

    #define GET_EVENT_BY_TYPE(snake_case, pascal_case) \
        inline const sf::Event::pascal_case* get_##snake_case() { \
            return __last_event->getIf<sf::Event::pascal_case>(); \
        }
    // GET_EVENT_BY_TYPE(closed, Closed) // sf::Event::Closed holds no data, no point in retrieving the object
    GET_EVENT_BY_TYPE(resized, Resized)
    // GET_EVENT_BY_TYPE(focus_lost, FocusLost) // sf::Event::FocusLost holds no data, no point in retrieving the object
    // GET_EVENT_BY_TYPE(focus_gained, FocusGained) // sf::Event::FocusGained holds no data, no point in retrieving the object
    // GET_EVENT_BY_TYPE(mouse_entered, MouseEntered) // sf::Event::MouseEntered holds no data, no point in retrieving the object
    // GET_EVENT_BY_TYPE(mouse_left, MouseLeft) // sf::Event::MouseLeft holds no data, no point in retrieving the object
    GET_EVENT_BY_TYPE(text_entered, TextEntered)
    GET_EVENT_BY_TYPE(key_pressed, KeyPressed)
    GET_EVENT_BY_TYPE(key_released, KeyReleased)
    GET_EVENT_BY_TYPE(mouse_wheel_scrolled, MouseWheelScrolled)
    GET_EVENT_BY_TYPE(mouse_button_pressed, MouseButtonPressed)
    GET_EVENT_BY_TYPE(mouse_button_released, MouseButtonReleased)
    GET_EVENT_BY_TYPE(mouse_moved, MouseMoved)
    GET_EVENT_BY_TYPE(joystick_button_pressed, JoystickButtonPressed)
    GET_EVENT_BY_TYPE(joystick_button_released, JoystickButtonReleased)
    GET_EVENT_BY_TYPE(joystick_moved, JoystickMoved)
    GET_EVENT_BY_TYPE(joystick_connected, JoystickConnected)
    GET_EVENT_BY_TYPE(joystick_disconnected, JoystickDisconnected)
    GET_EVENT_BY_TYPE(touch_began, TouchBegan)
    GET_EVENT_BY_TYPE(touch_moved, TouchMoved)
    GET_EVENT_BY_TYPE(touch_ended, TouchEnded)
    GET_EVENT_BY_TYPE(sensor_changed, SensorChanged)
    #undef GET_EVENT_BY_TYPE

    bool handle_event(const std::optional<sf::Event> event); // HEAD@handle_event

    std::optional<sf::Event> get_opt_event() { return __last_event; }
    bool key_pressed_is(sf::Keyboard::Key key); // HEAD@key_pressed_is
    bool key_released_is(sf::Keyboard::Key key); // HEAD@key_released_is
    sf::Vector2i get_mouse_pos() { return __last_mouse_pos; }


protected:
    std::vector<CALLBACK_BOOL> _on_closed = {};
    std::vector<CALLBACK_BOOL> _on_resized = {};
    std::vector<CALLBACK_BOOL> _on_focus_lost = {};
    std::vector<CALLBACK_BOOL> _on_focus_gained = {};
    std::vector<CALLBACK_BOOL> _on_mouse_entered = {};
    std::vector<CALLBACK_BOOL> _on_mouse_left = {};
    std::vector<CALLBACK_BOOL> _on_text_entered = {};
    std::vector<CALLBACK_BOOL> _on_key_pressed = {};
    std::vector<CALLBACK_BOOL> _on_key_released = {};
    std::vector<CALLBACK_BOOL> _on_mouse_wheel_scrolled = {};
    std::vector<CALLBACK_BOOL> _on_mouse_button_pressed = {};
    std::vector<CALLBACK_BOOL> _on_mouse_button_released = {};
    std::vector<CALLBACK_BOOL> _on_mouse_moved = {};
    std::vector<CALLBACK_BOOL> _on_joystick_button_pressed = {};
    std::vector<CALLBACK_BOOL> _on_joystick_button_released = {};
    std::vector<CALLBACK_BOOL> _on_joystick_moved = {};
    std::vector<CALLBACK_BOOL> _on_joystick_connected = {};
    std::vector<CALLBACK_BOOL> _on_joystick_disconnected = {};
    std::vector<CALLBACK_BOOL> _on_touch_began = {};
    std::vector<CALLBACK_BOOL> _on_touch_moved = {};
    std::vector<CALLBACK_BOOL> _on_touch_ended = {};
    std::vector<CALLBACK_BOOL> _on_sensor_changed = {};

private:
    std::vector<CALLBACK_BOOL> __get_callbacks(); // HEAD@__get_callbacks
    sf::Vector2i __get_last_mouse_pos(); // HEAD@__get_last_mouse_pos

    std::optional<sf::Event> __last_event = std::nullopt;
    sf::Vector2i __last_mouse_pos = {0, 0};

};
}
