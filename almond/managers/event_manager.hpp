#pragma once
#include "../core/globals.hpp"
#include "../events/event.hpp"

namespace nd {
class EventManager {
public:
    EventManager() {};

    #define ADD_CALLBACK(event_name) \
        inline void add_on_##event_name(CALLBACK_EVENT callback) { _on_##event_name.push_back(callback); }
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

    #define GET_EVENT_BY_TYPE(snake_case, pascal_case, upper_case) \
        inline nd::Event::pascal_case get_##snake_case() { \
            return __last_event.generic.type == nd::EventType::upper_case ? \
            __last_event.snake_case : nd::Event::pascal_case {}; \
        }
    GET_EVENT_BY_TYPE(mouse_moved, MouseMoved, MOUSE_MOVED)
    GET_EVENT_BY_TYPE(mouse_button_pressed, MouseButtonPressed, MOUSE_BUTTON_PRESSED)
    GET_EVENT_BY_TYPE(mouse_button_released, MouseButtonReleased, MOUSE_BUTTON_RELEASED)
    GET_EVENT_BY_TYPE(mouse_wheel_scrolled, MouseWheelScrolled, MOUSE_WHEEL_SCROLLED)
    GET_EVENT_BY_TYPE(key_pressed, KeyPressed, KEY_PRESSED)
    GET_EVENT_BY_TYPE(key_released, KeyReleased, KEY_RELEASED)
    GET_EVENT_BY_TYPE(resized, Resized, RESIZED)
    GET_EVENT_BY_TYPE(focus_lost, FocusLost, FOCUS_LOST)
    GET_EVENT_BY_TYPE(focus_gained, FocusGained, FOCUS_GAINED)
    GET_EVENT_BY_TYPE(mouse_entered, MouseEntered, MOUSE_ENTERED)
    GET_EVENT_BY_TYPE(mouse_left, MouseLeft, MOUSE_LEFT)
    GET_EVENT_BY_TYPE(text_entered, TextEntered, TEXT_ENTERED)
    GET_EVENT_BY_TYPE(joystick_button_pressed, JoystickButtonPressed, JOYSTICK_BUTTON_PRESSED)
    GET_EVENT_BY_TYPE(joystick_button_released, JoystickButtonReleased, JOYSTICK_BUTTON_RELEASED)
    GET_EVENT_BY_TYPE(joystick_moved, JoystickMoved, JOYSTICK_MOVED)
    GET_EVENT_BY_TYPE(joystick_connected, JoystickConnected, JOYSTICK_CONNECTED)
    GET_EVENT_BY_TYPE(joystick_disconnected, JoystickDisconnected, JOYSTICK_DISCONNECTED)
    GET_EVENT_BY_TYPE(touch_began, TouchBegan, TOUCH_BEGAN)
    GET_EVENT_BY_TYPE(touch_moved, TouchMoved, TOUCH_MOVED)
    GET_EVENT_BY_TYPE(touch_ended, TouchEnded, TOUCH_ENDED)
    GET_EVENT_BY_TYPE(sensor_changed, SensorChanged, SENSOR_CHANGED)
    GET_EVENT_BY_TYPE(closed, Closed, CLOSED)
    #undef GET_EVENT_BY_TYPE

    nd::Event get_event() { return __last_event; }

    void handle_event(const nd::Event& event); // HEAD@handle_event

protected:
    std::vector<CALLBACK_EVENT> _on_mouse_moved = {};
    std::vector<CALLBACK_EVENT> _on_mouse_button_pressed = {};
    std::vector<CALLBACK_EVENT> _on_mouse_button_released = {};
    std::vector<CALLBACK_EVENT> _on_mouse_wheel_scrolled = {};
    std::vector<CALLBACK_EVENT> _on_key_pressed = {};
    std::vector<CALLBACK_EVENT> _on_key_released = {};
    std::vector<CALLBACK_EVENT> _on_resized = {};
    std::vector<CALLBACK_EVENT> _on_focus_lost = {};
    std::vector<CALLBACK_EVENT> _on_focus_gained = {};
    std::vector<CALLBACK_EVENT> _on_mouse_entered = {};
    std::vector<CALLBACK_EVENT> _on_mouse_left = {};
    std::vector<CALLBACK_EVENT> _on_text_entered = {};
    std::vector<CALLBACK_EVENT> _on_joystick_button_pressed = {};
    std::vector<CALLBACK_EVENT> _on_joystick_button_released = {};
    std::vector<CALLBACK_EVENT> _on_joystick_moved = {};
    std::vector<CALLBACK_EVENT> _on_joystick_connected = {};
    std::vector<CALLBACK_EVENT> _on_joystick_disconnected = {};
    std::vector<CALLBACK_EVENT> _on_touch_began = {};
    std::vector<CALLBACK_EVENT> _on_touch_moved = {};
    std::vector<CALLBACK_EVENT> _on_touch_ended = {};
    std::vector<CALLBACK_EVENT> _on_sensor_changed = {};
    std::vector<CALLBACK_EVENT> _on_closed = {};

private:
    nd::Event __last_event = __INIT_EVENT_GENERIC;

};
}
