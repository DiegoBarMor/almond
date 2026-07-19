#pragma once
#include <iostream>
#include <functional>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "../parsers/strings.hpp"

#define CALLBACK_BOOL std::function<bool(const std::optional<sf::Event>)>
#define CALLBACK_VOID std::function<void()>
#define INTERSECTS_MOUSE(pos) contains_point(sf::Vector2f((float)pos.x, (float)pos.y))

namespace nd {
////////////////////////////////////////////////////////////////////////////////

class Widget {
public:
    // m.0a (Construction methods)
    Widget() {};
    virtual Widget* clone() { return new Widget(); }

    // m.0c (Lifecycle methods - SABHD)
    virtual bool set_spec(std::string key, std::string raw_value);
    virtual void add_child(Widget*);
    virtual void build();
    virtual bool handle_event(const std::optional<sf::Event> event);
    virtual void draw(sf::RenderWindow& window);

    // m.0d (Setters/Getters for the spec fields)
    void        set_weight  (float weight   ) { __weight = weight; }
    void        set_bg_color(sf::Color color);
    float       get_weight  ()                { return __weight;   }
    sf::Color   get_bg_color()                { return _bg_color;  }

    // m.0e (Setters/Getters for other internal fields)
    virtual void set_pos   (sf::Vector2f pos ) { _pos = pos;        }
    virtual void set_size  (sf::Vector2f size) { _size = size;      }
    void         set_parent(Widget* parent   ) { __parent = parent; }
    sf::Vector2f get_pos   ()                  { return _pos;       }
    sf::Vector2f get_size  ()                  { return _size;      }
    Widget*      get_parent()                  { return __parent;   }

    // m.0f (Linkers for the callbacks)
    virtual void link_on_window_closed          (CALLBACK_BOOL callback) { _on_window_closed           = callback; }
    virtual void link_on_window_resized         (CALLBACK_BOOL callback) { _on_window_resized          = callback; }
    virtual void link_on_window_focus_lost      (CALLBACK_BOOL callback) { _on_window_focus_lost       = callback; }
    virtual void link_on_window_focus_gained    (CALLBACK_BOOL callback) { _on_window_focus_gained     = callback; }
    virtual void link_on_window_mouse_enter     (CALLBACK_BOOL callback) { _on_window_mouse_enter      = callback; }
    virtual void link_on_window_mouse_leave     (CALLBACK_BOOL callback) { _on_window_mouse_leave      = callback; }
    virtual void link_on_text_entered           (CALLBACK_BOOL callback) { _on_text_entered            = callback; }
    virtual void link_on_key_press              (CALLBACK_BOOL callback) { _on_key_press               = callback; }
    virtual void link_on_key_release            (CALLBACK_BOOL callback) { _on_key_release             = callback; }
    virtual void link_on_mouse_wheel_scroll     (CALLBACK_BOOL callback) { _on_mouse_wheel_scroll      = callback; }
    virtual void link_on_mouse_click            (CALLBACK_BOOL callback) { _on_mouse_click             = callback; }
    virtual void link_on_mouse_release          (CALLBACK_BOOL callback) { _on_mouse_release           = callback; }
    virtual void link_on_mouse_move             (CALLBACK_BOOL callback) { _on_mouse_move              = callback; }
    virtual void link_on_joystick_button_press  (CALLBACK_BOOL callback) { _on_joystick_button_press   = callback; }
    virtual void link_on_joystick_button_release(CALLBACK_BOOL callback) { _on_joystick_button_release = callback; }
    virtual void link_on_joystick_move          (CALLBACK_BOOL callback) { _on_joystick_move           = callback; }
    virtual void link_on_joystick_connect       (CALLBACK_BOOL callback) { _on_joystick_connect        = callback; }
    virtual void link_on_joystick_disconnect    (CALLBACK_BOOL callback) { _on_joystick_disconnect     = callback; }
    virtual void link_on_touch_begin            (CALLBACK_BOOL callback) { _on_touch_begin             = callback; }
    virtual void link_on_touch_move             (CALLBACK_BOOL callback) { _on_touch_move              = callback; }
    virtual void link_on_touch_end              (CALLBACK_BOOL callback) { _on_touch_end               = callback; }
    virtual void link_on_sensor_change          (CALLBACK_BOOL callback) { _on_sensor_change           = callback; }

    // m.0g (Other functionalities)
    bool contains_point(sf::Vector2f point);
    void force_widget_square();

protected:
    // m.1a (Internal functionalities)
    void _init_shape();
    bool _internal_handle_event(const std::optional<sf::Event> event);

    // m.1b (Callback wrappers)
    virtual bool _internal_on_window_closed          (const std::optional<sf::Event> event);
    virtual bool _internal_on_window_resized         (const std::optional<sf::Event> event);
    virtual bool _internal_on_window_focus_lost      (const std::optional<sf::Event> event);
    virtual bool _internal_on_window_focus_gained    (const std::optional<sf::Event> event);
    virtual bool _internal_on_window_mouse_enter     (const std::optional<sf::Event> event);
    virtual bool _internal_on_window_mouse_leave     (const std::optional<sf::Event> event);
    virtual bool _internal_on_text_entered           (const std::optional<sf::Event> event);
    virtual bool _internal_on_key_press              (const std::optional<sf::Event> event);
    virtual bool _internal_on_key_release            (const std::optional<sf::Event> event);
    virtual bool _internal_on_mouse_wheel_scroll     (const std::optional<sf::Event> event);
    virtual bool _internal_on_mouse_click            (const std::optional<sf::Event> event);
    virtual bool _internal_on_mouse_release          (const std::optional<sf::Event> event);
    virtual bool _internal_on_mouse_move             (const std::optional<sf::Event> event);
    virtual bool _internal_on_joystick_button_press  (const std::optional<sf::Event> event);
    virtual bool _internal_on_joystick_button_release(const std::optional<sf::Event> event);
    virtual bool _internal_on_joystick_move          (const std::optional<sf::Event> event);
    virtual bool _internal_on_joystick_connect       (const std::optional<sf::Event> event);
    virtual bool _internal_on_joystick_disconnect    (const std::optional<sf::Event> event);
    virtual bool _internal_on_touch_begin            (const std::optional<sf::Event> event);
    virtual bool _internal_on_touch_move             (const std::optional<sf::Event> event);
    virtual bool _internal_on_touch_end              (const std::optional<sf::Event> event);
    virtual bool _internal_on_sensor_change          (const std::optional<sf::Event> event);

    // d.1c (Client callbacks)
    CALLBACK_BOOL _on_window_closed;
    CALLBACK_BOOL _on_window_resized;
    CALLBACK_BOOL _on_window_focus_lost;
    CALLBACK_BOOL _on_window_focus_gained;
    CALLBACK_BOOL _on_window_mouse_enter;
    CALLBACK_BOOL _on_window_mouse_leave;
    CALLBACK_BOOL _on_text_entered;
    CALLBACK_BOOL _on_key_press;
    CALLBACK_BOOL _on_key_release;
    CALLBACK_BOOL _on_mouse_wheel_scroll;
    CALLBACK_BOOL _on_mouse_click;
    CALLBACK_BOOL _on_mouse_release;
    CALLBACK_BOOL _on_mouse_move;
    CALLBACK_BOOL _on_joystick_button_press;
    CALLBACK_BOOL _on_joystick_button_release;
    CALLBACK_BOOL _on_joystick_move;
    CALLBACK_BOOL _on_joystick_connect;
    CALLBACK_BOOL _on_joystick_disconnect;
    CALLBACK_BOOL _on_touch_begin;
    CALLBACK_BOOL _on_touch_move;
    CALLBACK_BOOL _on_touch_end;
    CALLBACK_BOOL _on_sensor_change;

    // d.1d (Other fields)
    sf::Vector2f _pos  = {0, 0};
    sf::Vector2f _size = {0, 0};
    sf::RectangleShape _shape = sf::RectangleShape();
    sf::Color _bg_color = sf::Color::Transparent;

private:
    // d.2b (Spec fields)
    float __weight = 1.f;

    // d.2c (Other fields)
    Widget* __parent = nullptr;
};

////////////////////////////////////////////////////////////////////////////////
}
