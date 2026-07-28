#pragma once
#include <iostream>
#include <functional>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "../parsers/parser_strings.hpp"

#define CALLBACK_BOOL std::function<bool(const std::optional<sf::Event>)>
#define CALLBACK_VOID std::function<void()>
#define INTERSECTS_MOUSE(pos) contains_point(sf::Vector2f((float)pos.x, (float)pos.y))

namespace nd {
class Widget {
public:
    Widget() {};
    virtual Widget* clone() { return new Widget(); }

    virtual bool set_spec(std::string key, std::string raw_value); // HEAD@set_spec
    virtual void add_child(Widget* child); // HEAD@add_child
    virtual void build(); // HEAD@build
    virtual bool handle_event(const std::optional<sf::Event> event); // HEAD@handle_event
    virtual void draw(sf::RenderWindow& window); // HEAD@draw

    void        set_weight  (float weight   ) { __weight = weight; }
    void        set_bg_color(sf::Color color); // HEAD@set_bg_color
    float       get_weight  () { return __weight;  }
    sf::Color   get_bg_color() { return _bg_color; }

    virtual void set_pos   (sf::Vector2f pos ) { _pos = pos;        }
    virtual void set_size  (sf::Vector2f size) { _size = size;      }
    void         set_parent(Widget* parent   ) { __parent = parent; }
    sf::Vector2f get_pos   () { return _pos;     }
    sf::Vector2f get_size  () { return _size;    }
    Widget*      get_parent() { return __parent; }

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

    bool contains_point(sf::Vector2f point); // HEAD@contains_point
    void force_widget_square(); // HEAD@force_widget_square

protected:
    void _init_shape(); // HEAD@_init_shape
    bool _internal_handle_event(const std::optional<sf::Event> event); // HEAD@_internal_handle_event

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

    sf::Vector2f _pos  = {0, 0};
    sf::Vector2f _size = {0, 0};
    sf::RectangleShape _shape = sf::RectangleShape();
    sf::Color _bg_color = sf::Color::Transparent;

private:
    float __weight = 1.f;

    Widget* __parent = nullptr;
};
}
