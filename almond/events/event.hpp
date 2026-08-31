#pragma once
#include "../core/globals.hpp"

namespace nd {
enum class EventType {
    NONE,
    MOUSE_MOVED,
    MOUSE_BUTTON_PRESSED,
    MOUSE_BUTTON_RELEASED,
    MOUSE_WHEEL_SCROLLED,
    KEY_PRESSED,
    KEY_RELEASED,
    RESIZED,
    FOCUS_LOST,
    FOCUS_GAINED,
    MOUSE_ENTERED,
    MOUSE_LEFT,
    TEXT_ENTERED,
    JOYSTICK_BUTTON_PRESSED,
    JOYSTICK_BUTTON_RELEASED,
    JOYSTICK_MOVED,
    JOYSTICK_CONNECTED,
    JOYSTICK_DISCONNECTED,
    TOUCH_BEGAN,
    TOUCH_MOVED,
    TOUCH_ENDED,
    SENSOR_CHANGED,
    CLOSED,
};

union Event {
    struct None {
        EventType type {EventType::NONE};
    } none;

    struct MouseMoved {
        EventType type {EventType::MOUSE_MOVED};
        sf::Vector2i position;
    } mouse_moved;

    struct MouseButtonPressed {
        EventType type {EventType::MOUSE_BUTTON_PRESSED};
        sf::Vector2i position;
        sf::Mouse::Button button;
    } mouse_button_pressed;

    struct MouseButtonReleased {
        EventType type {EventType::MOUSE_BUTTON_RELEASED};
        sf::Vector2i position;
        sf::Mouse::Button button;
    } mouse_button_released;

    struct MouseWheelScrolled {
        EventType type {EventType::MOUSE_WHEEL_SCROLLED};
        sf::Vector2i position;
        sf::Mouse::Wheel wheel;
        float delta;
    } mouse_wheel_scrolled;

    struct KeyPressed {
        EventType type {EventType::KEY_PRESSED};
        bool alt;
        bool shift;
        bool control;
        bool system;
        sf::Keyboard::Key code;
        sf::Keyboard::Scancode scancode;
    } key_pressed;

    struct KeyReleased {
        EventType type {EventType::KEY_RELEASED};
        bool alt;
        bool shift;
        bool control;
        bool system;
        sf::Keyboard::Key code;
        sf::Keyboard::Scancode scancode;
    } key_released;

    struct Resized {
        EventType type {EventType::RESIZED};
        sf::Vector2u size;
    } resized;

    struct FocusLost {
        EventType type {EventType::FOCUS_LOST};
    } focus_lost;

    struct FocusGained {
        EventType type {EventType::FOCUS_GAINED};
    } focus_gained;

    struct MouseEntered {
        EventType type {EventType::MOUSE_ENTERED};
    } mouse_entered;

    struct MouseLeft {
        EventType type {EventType::MOUSE_LEFT};
    } mouse_left;

    struct TextEntered {
        EventType type {EventType::TEXT_ENTERED};
        char32_t unicode;
    } text_entered;

    struct JoystickButtonPressed {
        EventType type {EventType::JOYSTICK_BUTTON_PRESSED};
        unsigned int joystick_id;
        unsigned int button;
    } joystick_button_pressed;

    struct JoystickButtonReleased {
        EventType type {EventType::JOYSTICK_BUTTON_RELEASED};
        unsigned int joystick_id;
        unsigned int button;
    } joystick_button_released;

    struct JoystickMoved {
        EventType type {EventType::JOYSTICK_MOVED};
        unsigned int joystick_id;
        sf::Joystick::Axis axis;
        float position;
    } joystick_moved;

    struct JoystickConnected {
        EventType type {EventType::JOYSTICK_CONNECTED};
        unsigned int joystick_id;
    } joystick_connected;

    struct JoystickDisconnected {
        EventType type {EventType::JOYSTICK_DISCONNECTED};
        unsigned int joystick_id;
    } joystick_disconnected;

    struct TouchBegan {
        EventType type {EventType::TOUCH_BEGAN};
        unsigned int finger;
        sf::Vector2i position;
    } touch_began;

    struct TouchMoved {
        EventType type {EventType::TOUCH_MOVED};
        unsigned int finger;
        sf::Vector2i position;
    } touch_moved;

    struct TouchEnded {
        EventType type {EventType::TOUCH_ENDED};
        unsigned int finger;
        sf::Vector2i position;
    } touch_ended;

    struct SensorChanged {
        EventType type {EventType::SENSOR_CHANGED};
        sf::Sensor::Type type_sensor;
        sf::Vector3f value;
    } sensor_changed;

    struct Closed {
        EventType type {EventType::CLOSED};
    } closed;
};

#define WRAPPER_START(event_type, struct_name) \
    if (sf_event->is<sf::Event::event_type>()) { \
        const auto sf_data = sf_event->getIf<sf::Event::event_type>(); \
        if (sf_data) return nd::Event {.struct_name {

#define WRAPPER_END \
        }}; \
    };

#define __INIT_EVENT_NONE nd::Event {.none {}}

inline nd::Event __init_event(const std::optional<sf::Event> sf_event) {
    WRAPPER_START(MouseMoved, mouse_moved)
        .position = sf_data->position,
    WRAPPER_END

    WRAPPER_START(MouseButtonPressed, mouse_button_pressed)
        .position = sf_data->position,
        .button   = sf_data->button,
    WRAPPER_END

    WRAPPER_START(MouseButtonReleased, mouse_button_released)
        .position = sf_data->position,
        .button   = sf_data->button,
    WRAPPER_END

    WRAPPER_START(MouseWheelScrolled, mouse_wheel_scrolled)
        .position = sf_data->position,
        .wheel    = sf_data->wheel,
        .delta    = sf_data->delta,
    WRAPPER_END

    WRAPPER_START(KeyPressed, key_pressed)
        .alt      = sf_data->alt,
        .shift    = sf_data->shift,
        .control  = sf_data->control,
        .system   = sf_data->system,
        .code     = sf_data->code,
        .scancode = sf_data->scancode,
    WRAPPER_END

    WRAPPER_START(KeyReleased, key_released)
        .alt      = sf_data->alt,
        .shift    = sf_data->shift,
        .control  = sf_data->control,
        .system   = sf_data->system,
        .code     = sf_data->code,
        .scancode = sf_data->scancode,
    WRAPPER_END

    WRAPPER_START(Resized, resized)
        .size     = sf_data->size,
    WRAPPER_END

    WRAPPER_START(FocusLost, focus_lost)
    WRAPPER_END

    WRAPPER_START(FocusGained, focus_gained)
    WRAPPER_END

    WRAPPER_START(MouseEntered, mouse_entered)
    WRAPPER_END

    WRAPPER_START(MouseLeft, mouse_left)
    WRAPPER_END

    WRAPPER_START(TextEntered, text_entered)
        .unicode  = sf_data->unicode,
    WRAPPER_END

    WRAPPER_START(JoystickButtonPressed, joystick_button_pressed)
        .joystick_id = sf_data->joystickId,
        .button      = sf_data->button,
    WRAPPER_END

    WRAPPER_START(JoystickButtonReleased, joystick_button_released)
        .joystick_id = sf_data->joystickId,
        .button      = sf_data->button,
    WRAPPER_END

    WRAPPER_START(JoystickMoved, joystick_moved)
        .joystick_id = sf_data->joystickId,
        .axis        = sf_data->axis,
        .position    = sf_data->position,
    WRAPPER_END

    WRAPPER_START(JoystickConnected, joystick_connected)
        .joystick_id = sf_data->joystickId,
    WRAPPER_END

    WRAPPER_START(JoystickDisconnected, joystick_disconnected)
        .joystick_id = sf_data->joystickId,
    WRAPPER_END

    WRAPPER_START(TouchBegan, touch_began)
        .finger   = sf_data->finger,
        .position = sf_data->position,
    WRAPPER_END

    WRAPPER_START(TouchMoved, touch_moved)
        .finger   = sf_data->finger,
        .position = sf_data->position,
    WRAPPER_END

    WRAPPER_START(TouchEnded, touch_ended)
        .finger   = sf_data->finger,
        .position = sf_data->position,
    WRAPPER_END

    WRAPPER_START(SensorChanged, sensor_changed)
        .type_sensor = sf_data->type,
        .value       = sf_data->value,
    WRAPPER_END

    WRAPPER_START(Closed, closed)
    WRAPPER_END

    return __INIT_EVENT_NONE;
}
#undef WRAPPER_START
#undef WRAPPER_END

}
