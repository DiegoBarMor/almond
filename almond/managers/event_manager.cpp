#include "event_manager.hpp"

// -----------------------------------------------------------------------------
void nd::EventManager::handle_event(const nd::Event& event) { // FUNC@handle_event
    __last_event = event;
    std::vector<CALLBACK_EVENT> callbacks;

    switch (event.generic.type) {
        case nd::EventType::MOUSE_MOVED:              callbacks = _on_mouse_moved; break;
        case nd::EventType::MOUSE_BUTTON_PRESSED:     callbacks = _on_mouse_button_pressed; break;
        case nd::EventType::MOUSE_BUTTON_RELEASED:    callbacks = _on_mouse_button_released; break;
        case nd::EventType::MOUSE_WHEEL_SCROLLED:     callbacks = _on_mouse_wheel_scrolled; break;
        case nd::EventType::KEY_PRESSED:              callbacks = _on_key_pressed; break;
        case nd::EventType::KEY_RELEASED:             callbacks = _on_key_released; break;
        case nd::EventType::RESIZED:                  callbacks = _on_resized; break;
        case nd::EventType::FOCUS_LOST:               callbacks = _on_focus_lost; break;
        case nd::EventType::FOCUS_GAINED:             callbacks = _on_focus_gained; break;
        case nd::EventType::MOUSE_ENTERED:            callbacks = _on_mouse_entered; break;
        case nd::EventType::MOUSE_LEFT:               callbacks = _on_mouse_left; break;
        case nd::EventType::TEXT_ENTERED:             callbacks = _on_text_entered; break;
        case nd::EventType::JOYSTICK_BUTTON_PRESSED:  callbacks = _on_joystick_button_pressed; break;
        case nd::EventType::JOYSTICK_BUTTON_RELEASED: callbacks = _on_joystick_button_released; break;
        case nd::EventType::JOYSTICK_MOVED:           callbacks = _on_joystick_moved; break;
        case nd::EventType::JOYSTICK_CONNECTED:       callbacks = _on_joystick_connected; break;
        case nd::EventType::JOYSTICK_DISCONNECTED:    callbacks = _on_joystick_disconnected; break;
        case nd::EventType::TOUCH_BEGAN:              callbacks = _on_touch_began; break;
        case nd::EventType::TOUCH_MOVED:              callbacks = _on_touch_moved; break;
        case nd::EventType::TOUCH_ENDED:              callbacks = _on_touch_ended; break;
        case nd::EventType::SENSOR_CHANGED:           callbacks = _on_sensor_changed; break;
        case nd::EventType::CLOSED:                   callbacks = _on_closed; break;
        default: callbacks = {}; break;
    }

    for (CALLBACK_EVENT callback : callbacks) {
        bool consumed = callback(event);
        if (consumed) return;
    }
} // END@handle_event


// -----------------------------------------------------------------------------
