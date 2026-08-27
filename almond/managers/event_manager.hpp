#pragma once
#include "../core/globals.hpp"

#define ADD_CALLBACK(event_name) \
    inline void add_on_##event_name(CALLBACK_BOOL callback) { _on_##event_name.push_back(callback); }

namespace nd {
class EventManager {
public:
    EventManager() {};
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
    bool handle_event(const std::optional<sf::Event> event); // HEAD@handle_event

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
    std::vector<CALLBACK_BOOL> __get_callbacks(const std::optional<sf::Event> event); // HEAD@__get_callbacks

};
}
