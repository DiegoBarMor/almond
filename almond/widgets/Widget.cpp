#include "Widget.hpp"

////////////////////////////////////////////////////////////////////////////////

std::unordered_map<std::string, nd::Widget*> nd::Widget::_prototypes = {};
std::unordered_map<std::string, nd::Widget*> nd::Widget::_table_id_widgets = {};

nd::Widget* nd::Widget::GUIFactory(std::string type) {
    if (_prototypes.find(type) != _prototypes.end()) {
        nd::Widget* widget = _prototypes[type]->clone();
        return widget;
    }
    std::cerr << "Invalid GUI type: " << type << std::endl;
    return nullptr;
}

nd::Widget* nd::Widget::get_widget_by_id(std::string id) {
    return _table_id_widgets[id];
}

void nd::Widget::add_prototype(std::string type, nd::Widget* prototype) {
    _prototypes[type] = prototype;
}

bool nd::Widget::set_spec(std::string key, std::string raw_value) {
    if (key == "ID" || key == "IDENTIFIER") {
        set_id(raw_value);
        return true;
    }
    if (key == "W" || key == "WEIGHT") {
        __weight = nd::parse_float_string(raw_value);
        return true;
    }
    if (key == "BG" || key == "BG_COLOR") {
        _bg_color = nd::parse_color_string(raw_value);
        return true;
    }
    return false;
}

void nd::Widget::add_child(nd::Widget* child) {
    std::cerr << "Can't add child to non-container widget" << std::endl;
}

void nd::Widget::build() {
    _init_shape();
}

bool nd::Widget::handle_event(sf::Event event) {
    return _internal_handle_event(event);
}

void nd::Widget::draw(sf::RenderWindow& window) {
    window.draw(_shape);
}

void nd::Widget::set_id(std::string id) {
    __id = id;
    _table_id_widgets[id] = this;
}

void nd::Widget::set_bg_color(sf::Color color) {
    _bg_color = color;
    _shape.setFillColor(color);
}

bool nd::Widget::contains_point(sf::Vector2f point) {
    return _shape.getGlobalBounds().contains(point);
}

void nd::Widget::force_widget_square() {
    sf::Vector2f size = get_size();
    float short_side = std::min(size.x, size.y);
    sf::Vector2f pos = get_pos();

    if (short_side == size.x) {
        pos.y += (size.y - short_side) / 2.0f;
    } else {
        pos.x += (size.x - short_side) / 2.0f;
    }
    set_pos(pos);
    set_size(sf::Vector2f(short_side, short_side));
}

void nd::Widget::_init_shape() {
    _shape.setSize(_size);
    _shape.setPosition(_pos);
    _shape.setFillColor(get_bg_color());
}

bool nd::Widget::_internal_handle_event(sf::Event event) {
    switch (event.type) {
        case sf::Event::Closed:                 return _internal_on_window_closed(event);
        case sf::Event::Resized:                return _internal_on_window_resized(event);
        case sf::Event::LostFocus:              return _internal_on_window_lost_focus(event);
        case sf::Event::GainedFocus:            return _internal_on_window_gained_focus(event);
        case sf::Event::MouseEntered:           return _internal_on_window_mouse_enter(event);
        case sf::Event::MouseLeft:              return _internal_on_window_mouse_leave(event);
        case sf::Event::TextEntered:            return _internal_on_text_entered(event);
        case sf::Event::KeyPressed:             return _internal_on_key_press(event);
        case sf::Event::KeyReleased:            return _internal_on_key_release(event);
        case sf::Event::MouseWheelScrolled:     return _internal_on_mouse_wheel_scroll(event);
        case sf::Event::MouseButtonPressed:     return _internal_on_mouse_click(event);
        case sf::Event::MouseButtonReleased:    return _internal_on_mouse_release(event);
        case sf::Event::MouseMoved:             return _internal_on_mouse_move(event);
        case sf::Event::JoystickButtonPressed:  return _internal_on_joystick_button_press(event);
        case sf::Event::JoystickButtonReleased: return _internal_on_joystick_button_release(event);
        case sf::Event::JoystickMoved:          return _internal_on_joystick_move(event);
        case sf::Event::JoystickConnected:      return _internal_on_joystick_connect(event);
        case sf::Event::JoystickDisconnected:   return _internal_on_joystick_disconnect(event);
        case sf::Event::TouchBegan:             return _internal_on_touch_begin(event);
        case sf::Event::TouchMoved:             return _internal_on_touch_move(event);
        case sf::Event::TouchEnded:             return _internal_on_touch_end(event);
        case sf::Event::SensorChanged:          return _internal_on_sensor_change(event);
        default: return false;
    }
}

bool nd::Widget::_internal_on_window_closed(sf::Event event) {
    if (_on_window_closed) { return _on_window_closed(event); }
    return false;
}

bool nd::Widget::_internal_on_window_resized(sf::Event event) {
    if (_on_window_resized) { return _on_window_resized(event); }
    return false;
}

bool nd::Widget::_internal_on_window_lost_focus(sf::Event event) {
    if (_on_window_lost_focus) { return _on_window_lost_focus(event); }
    return false;
}

bool nd::Widget::_internal_on_window_gained_focus(sf::Event event) {
    if (_on_window_gained_focus) { return _on_window_gained_focus(event); }
    return false;
}

bool nd::Widget::_internal_on_window_mouse_enter(sf::Event event) {
    if (_on_window_mouse_enter) { return _on_window_mouse_enter(event); }
    return false;
}

bool nd::Widget::_internal_on_window_mouse_leave(sf::Event event) {
    if (_on_window_mouse_leave) { return _on_window_mouse_leave(event); }
    return false;
}

bool nd::Widget::_internal_on_text_entered(sf::Event event) {
    if (_on_text_entered) { return _on_text_entered(event); }
    return false;
}

bool nd::Widget::_internal_on_key_press(sf::Event event) {
    if (_on_key_press) { return _on_key_press(event); }
    return false;
}

bool nd::Widget::_internal_on_key_release(sf::Event event) {
    if (_on_key_release) { return _on_key_release(event); }
    return false;
}

bool nd::Widget::_internal_on_mouse_wheel_scroll(sf::Event event) {
    if (_on_mouse_wheel_scroll) { return _on_mouse_wheel_scroll(event); }
    return false;
}

bool nd::Widget::_internal_on_mouse_click(sf::Event event) {
    if (_on_mouse_click && INTERSECTS_MOUSE(event.mouseButton)) {
        return _on_mouse_click(event);
    }
    return false;
}

bool nd::Widget::_internal_on_mouse_release(sf::Event event) {
    if (_on_mouse_release && INTERSECTS_MOUSE(event.mouseButton)) {
        return _on_mouse_release(event);
    }
    return false;
}

bool nd::Widget::_internal_on_mouse_move(sf::Event event) {
    if (_on_mouse_move && INTERSECTS_MOUSE(event.mouseMove)) {
        return _on_mouse_move(event);
    }
    return false;
}

bool nd::Widget::_internal_on_joystick_button_press(sf::Event event) {
    if (_on_joystick_button_press) { return _on_joystick_button_press(event); }
    return false;
}

bool nd::Widget::_internal_on_joystick_button_release(sf::Event event) {
    if (_on_joystick_button_release) { return _on_joystick_button_release(event); }
    return false;
}

bool nd::Widget::_internal_on_joystick_move(sf::Event event) {
    if (_on_joystick_move) { return _on_joystick_move(event); }
    return false;
}

bool nd::Widget::_internal_on_joystick_connect(sf::Event event) {
    if (_on_joystick_connect) { return _on_joystick_connect(event); }
    return false;
}

bool nd::Widget::_internal_on_joystick_disconnect(sf::Event event) {
    if (_on_joystick_disconnect) { return _on_joystick_disconnect(event); }
    return false;
}

bool nd::Widget::_internal_on_touch_begin(sf::Event event) {
    if (_on_touch_begin) { return _on_touch_begin(event); }
    return false;
}

bool nd::Widget::_internal_on_touch_move(sf::Event event) {
    if (_on_touch_move) { return _on_touch_move(event); }
    return false;
}

bool nd::Widget::_internal_on_touch_end(sf::Event event) {
    if (_on_touch_end) { return _on_touch_end(event); }
    return false;
}

bool nd::Widget::_internal_on_sensor_change(sf::Event event) {
    if (_on_sensor_change) { return _on_sensor_change(event); }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
