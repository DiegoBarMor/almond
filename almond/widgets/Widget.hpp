#pragma once
#include <iostream>
#include <functional>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../parsers/strings.hpp"

#define CALLBACK_BOOL std::function<bool(sf::Event)>
#define CALLBACK_VOID std::function<void()>
#define INTERSECTS_MOUSE(pos) contains_point(sf::Vector2f((float)pos.x, (float)pos.y))

namespace nd {
////////////////////////////////////////////////////////////////////////////////

class Widget {
public:
    // m.0a (Construction methods)
    Widget() {};
    static Widget* GUIFactory(std::string type);
    virtual Widget* clone() { return new Widget(); }

    // m.0b (Static methods)
    static Widget* get_widget_by_id(std::string id);
    static void add_prototype(std::string type, Widget* prototype);

    // m.0c (Lifecycle methods - SABHD)
    virtual bool set_spec(std::string key, std::string raw_value);
    virtual void add_child(Widget*);
    virtual void build();
    virtual bool handle_event(sf::Event event);
    virtual void draw(sf::RenderWindow& window);

    // m.0d (Setters/Getters for the spec fields)
    void        set_id      (std::string id );
    void        set_weight  (float weight   ) { __weight = weight; }
    void        set_bg_color(sf::Color color);
    std::string get_id      ()                { return __id;       }
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
    virtual void link_on_window_lost_focus      (CALLBACK_BOOL callback) { _on_window_lost_focus       = callback; }
    virtual void link_on_window_gained_focus    (CALLBACK_BOOL callback) { _on_window_gained_focus     = callback; }
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
    bool _internal_handle_event(sf::Event event);

    // m.1b (Callback wrappers)
    virtual bool _internal_on_window_closed          (sf::Event event);
    virtual bool _internal_on_window_resized         (sf::Event event);
    virtual bool _internal_on_window_lost_focus      (sf::Event event);
    virtual bool _internal_on_window_gained_focus    (sf::Event event);
    virtual bool _internal_on_window_mouse_enter     (sf::Event event);
    virtual bool _internal_on_window_mouse_leave     (sf::Event event);
    virtual bool _internal_on_text_entered           (sf::Event event);
    virtual bool _internal_on_key_press              (sf::Event event);
    virtual bool _internal_on_key_release            (sf::Event event);
    virtual bool _internal_on_mouse_wheel_scroll     (sf::Event event);
    virtual bool _internal_on_mouse_click            (sf::Event event);
    virtual bool _internal_on_mouse_release          (sf::Event event);
    virtual bool _internal_on_mouse_move             (sf::Event event);
    virtual bool _internal_on_joystick_button_press  (sf::Event event);
    virtual bool _internal_on_joystick_button_release(sf::Event event);
    virtual bool _internal_on_joystick_move          (sf::Event event);
    virtual bool _internal_on_joystick_connect       (sf::Event event);
    virtual bool _internal_on_joystick_disconnect    (sf::Event event);
    virtual bool _internal_on_touch_begin            (sf::Event event);
    virtual bool _internal_on_touch_move             (sf::Event event);
    virtual bool _internal_on_touch_end              (sf::Event event);
    virtual bool _internal_on_sensor_change          (sf::Event event);

    // d.1a (Static fields)
    static std::unordered_map<std::string, Widget*> _prototypes;
    static std::unordered_map<std::string, Widget*> _table_id_widgets;

    // d.1c (Client callbacks)
    CALLBACK_BOOL _on_window_closed;
    CALLBACK_BOOL _on_window_resized;
    CALLBACK_BOOL _on_window_lost_focus;
    CALLBACK_BOOL _on_window_gained_focus;
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
    std::string __id = "";
    float __weight = 1.f;

    // d.2c (Other fields)
    Widget* __parent = nullptr;
};

////////////////////////////////////////////////////////////////////////////////
}
