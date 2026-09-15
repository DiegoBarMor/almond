#pragma once
#include "../core/globals.hpp"
#include "../events/event.hpp"

namespace nd {
class EventManager {
public:
    EventManager() {};

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

private:
    nd::Event __last_event = __INIT_EVENT_GENERIC;

};
}
