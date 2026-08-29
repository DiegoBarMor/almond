#include "event_manager.hpp"

// -----------------------------------------------------------------------------
void nd::EventManager::manage_events(sf::RenderWindow& window) { // FUNC@manage_events
    while (const std::optional event = window.pollEvent())
        __handle_event_generic(event);
} // END@manage_events


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
void nd::EventManager::__handle_event_generic(const std::optional<sf::Event> event) { // FUNC@__handle_event_generic
    __last_event = event;
    std::vector<CALLBACK_BOOL> callbacks;

    if (event->is<sf::Event::MouseMoved>()) {
        callbacks = _on_mouse_moved;
        const auto mouse_moved = event->getIf<sf::Event::MouseMoved>();
        if (mouse_moved) __last_mouse_pos = mouse_moved->position;
    }
    else if (event->is<sf::Event::MouseButtonPressed>()) {
        callbacks = _on_mouse_button_pressed;
        const auto mouse_button_pressed = event->getIf<sf::Event::MouseButtonPressed>();
        if (mouse_button_pressed) __last_mouse_pos = mouse_button_pressed->position;
    }
    else if (event->is<sf::Event::MouseButtonReleased>()) {
        callbacks = _on_mouse_button_released;
        const auto mouse_button_released = event->getIf<sf::Event::MouseButtonReleased>();
        if (mouse_button_released) __last_mouse_pos = mouse_button_released->position;
    }
    else if (event->is<sf::Event::MouseWheelScrolled>()) {
        callbacks = _on_mouse_wheel_scrolled;
        const auto mouse_wheel_scrolled = event->getIf<sf::Event::MouseWheelScrolled>();
        if (mouse_wheel_scrolled) __last_mouse_pos = mouse_wheel_scrolled->position;
    }
    else if (event->is<sf::Event::Closed>())                 callbacks = _on_closed;
    else if (event->is<sf::Event::Resized>())                callbacks = _on_resized;
    else if (event->is<sf::Event::FocusLost>())              callbacks = _on_focus_lost;
    else if (event->is<sf::Event::FocusGained>())            callbacks = _on_focus_gained;
    else if (event->is<sf::Event::MouseEntered>())           callbacks = _on_mouse_entered;
    else if (event->is<sf::Event::MouseLeft>())              callbacks = _on_mouse_left;
    else if (event->is<sf::Event::TextEntered>())            callbacks = _on_text_entered;
    else if (event->is<sf::Event::KeyPressed>())             callbacks = _on_key_pressed;
    else if (event->is<sf::Event::KeyReleased>())            callbacks = _on_key_released;
    else if (event->is<sf::Event::JoystickButtonPressed>())  callbacks = _on_joystick_button_pressed;
    else if (event->is<sf::Event::JoystickButtonReleased>()) callbacks = _on_joystick_button_released;
    else if (event->is<sf::Event::JoystickMoved>())          callbacks = _on_joystick_moved;
    else if (event->is<sf::Event::JoystickConnected>())      callbacks = _on_joystick_connected;
    else if (event->is<sf::Event::JoystickDisconnected>())   callbacks = _on_joystick_disconnected;
    else if (event->is<sf::Event::TouchBegan>())             callbacks = _on_touch_began;
    else if (event->is<sf::Event::TouchMoved>())             callbacks = _on_touch_moved;
    else if (event->is<sf::Event::TouchEnded>())             callbacks = _on_touch_ended;
    else if (event->is<sf::Event::SensorChanged>())          callbacks = _on_sensor_changed;
    else callbacks = {};

    for (CALLBACK_BOOL callback : callbacks) {
        bool consumed = callback();
        if (consumed) return;
    }
} // END@__handle_event_generic


// -----------------------------------------------------------------------------
