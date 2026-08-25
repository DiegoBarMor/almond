#pragma once
#include "../core/globals.hpp"

namespace nd {
class Behavior {
public:
    Behavior() {};
    virtual void link_on_closed                  (CALLBACK_BOOL callback) { _on_closed                   = callback; }
    virtual void link_on_resized                 (CALLBACK_BOOL callback) { _on_resized                  = callback; }
    virtual void link_on_focus_lost              (CALLBACK_BOOL callback) { _on_focus_lost               = callback; }
    virtual void link_on_focus_gained            (CALLBACK_BOOL callback) { _on_focus_gained             = callback; }
    virtual void link_on_mouse_entered           (CALLBACK_BOOL callback) { _on_mouse_entered            = callback; }
    virtual void link_on_mouse_left              (CALLBACK_BOOL callback) { _on_mouse_left               = callback; }
    virtual void link_on_text_entered            (CALLBACK_BOOL callback) { _on_text_entered             = callback; }
    virtual void link_on_key_pressed             (CALLBACK_BOOL callback) { _on_key_pressed              = callback; }
    virtual void link_on_key_released            (CALLBACK_BOOL callback) { _on_key_released             = callback; }
    virtual void link_on_mouse_wheel_scrolled    (CALLBACK_BOOL callback) { _on_mouse_wheel_scrolled     = callback; }
    virtual void link_on_mouse_button_pressed    (CALLBACK_BOOL callback) { _on_mouse_button_pressed     = callback; }
    virtual void link_on_mouse_button_released   (CALLBACK_BOOL callback) { _on_mouse_button_released    = callback; }
    virtual void link_on_mouse_moved             (CALLBACK_BOOL callback) { _on_mouse_moved              = callback; }
    virtual void link_on_joystick_button_pressed (CALLBACK_BOOL callback) { _on_joystick_button_pressed  = callback; }
    virtual void link_on_joystick_button_released(CALLBACK_BOOL callback) { _on_joystick_button_released = callback; }
    virtual void link_on_joystick_moved          (CALLBACK_BOOL callback) { _on_joystick_moved           = callback; }
    virtual void link_on_joystick_connected      (CALLBACK_BOOL callback) { _on_joystick_connected       = callback; }
    virtual void link_on_joystick_disconnected   (CALLBACK_BOOL callback) { _on_joystick_disconnected    = callback; }
    virtual void link_on_touch_began             (CALLBACK_BOOL callback) { _on_touch_began              = callback; }
    virtual void link_on_touch_moved             (CALLBACK_BOOL callback) { _on_touch_moved              = callback; }
    virtual void link_on_touch_ended             (CALLBACK_BOOL callback) { _on_touch_ended              = callback; }
    virtual void link_on_sensor_changed          (CALLBACK_BOOL callback) { _on_sensor_changed           = callback; }
    bool handle_event(const std::optional<sf::Event> event); // HEAD@handle_event

protected:
    virtual bool _internal_on_closed                  (const std::optional<sf::Event> event); // HEAD@_internal_on_closed
    virtual bool _internal_on_resized                 (const std::optional<sf::Event> event); // HEAD@_internal_on_resized
    virtual bool _internal_on_focus_lost              (const std::optional<sf::Event> event); // HEAD@_internal_on_focus_lost
    virtual bool _internal_on_focus_gained            (const std::optional<sf::Event> event); // HEAD@_internal_on_focus_gained
    virtual bool _internal_on_mouse_entered           (const std::optional<sf::Event> event); // HEAD@_internal_on_mouse_entered
    virtual bool _internal_on_mouse_left              (const std::optional<sf::Event> event); // HEAD@_internal_on_mouse_left
    virtual bool _internal_on_text_entered            (const std::optional<sf::Event> event); // HEAD@_internal_on_text_entered
    virtual bool _internal_on_key_pressed             (const std::optional<sf::Event> event); // HEAD@_internal_on_key_pressed
    virtual bool _internal_on_key_released            (const std::optional<sf::Event> event); // HEAD@_internal_on_key_released
    virtual bool _internal_on_mouse_wheel_scrolled    (const std::optional<sf::Event> event); // HEAD@_internal_on_mouse_wheel_scrolled
    virtual bool _internal_on_mouse_button_pressed    (const std::optional<sf::Event> event); // HEAD@_internal_on_mouse_button_pressed
    virtual bool _internal_on_mouse_button_released   (const std::optional<sf::Event> event); // HEAD@_internal_on_mouse_button_released
    virtual bool _internal_on_mouse_moved             (const std::optional<sf::Event> event); // HEAD@_internal_on_mouse_moved
    virtual bool _internal_on_joystick_button_pressed (const std::optional<sf::Event> event); // HEAD@_internal_on_joystick_button_pressed
    virtual bool _internal_on_joystick_button_released(const std::optional<sf::Event> event); // HEAD@_internal_on_joystick_button_released
    virtual bool _internal_on_joystick_moved          (const std::optional<sf::Event> event); // HEAD@_internal_on_joystick_moved
    virtual bool _internal_on_joystick_connected      (const std::optional<sf::Event> event); // HEAD@_internal_on_joystick_connected
    virtual bool _internal_on_joystick_disconnected   (const std::optional<sf::Event> event); // HEAD@_internal_on_joystick_disconnected
    virtual bool _internal_on_touch_began             (const std::optional<sf::Event> event); // HEAD@_internal_on_touch_began
    virtual bool _internal_on_touch_moved             (const std::optional<sf::Event> event); // HEAD@_internal_on_touch_moved
    virtual bool _internal_on_touch_ended             (const std::optional<sf::Event> event); // HEAD@_internal_on_touch_ended
    virtual bool _internal_on_sensor_changed          (const std::optional<sf::Event> event); // HEAD@_internal_on_sensor_changed

    CALLBACK_BOOL _on_closed;
    CALLBACK_BOOL _on_resized;
    CALLBACK_BOOL _on_focus_lost;
    CALLBACK_BOOL _on_focus_gained;
    CALLBACK_BOOL _on_mouse_entered;
    CALLBACK_BOOL _on_mouse_left;
    CALLBACK_BOOL _on_text_entered;
    CALLBACK_BOOL _on_key_pressed;
    CALLBACK_BOOL _on_key_released;
    CALLBACK_BOOL _on_mouse_wheel_scrolled;
    CALLBACK_BOOL _on_mouse_button_pressed;
    CALLBACK_BOOL _on_mouse_button_released;
    CALLBACK_BOOL _on_mouse_moved;
    CALLBACK_BOOL _on_joystick_button_pressed;
    CALLBACK_BOOL _on_joystick_button_released;
    CALLBACK_BOOL _on_joystick_moved;
    CALLBACK_BOOL _on_joystick_connected;
    CALLBACK_BOOL _on_joystick_disconnected;
    CALLBACK_BOOL _on_touch_began;
    CALLBACK_BOOL _on_touch_moved;
    CALLBACK_BOOL _on_touch_ended;
    CALLBACK_BOOL _on_sensor_changed;

};
}
