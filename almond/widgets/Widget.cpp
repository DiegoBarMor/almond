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

bool nd::Widget::handle_event(const std::optional<sf::Event> event) {
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

bool nd::Widget::_internal_handle_event(const std::optional<sf::Event> event) {
    if (event->is<sf::Event::Closed>())                 return _internal_on_window_closed(event);
    if (event->is<sf::Event::Resized>())                return _internal_on_window_resized(event);
    if (event->is<sf::Event::FocusLost>())              return _internal_on_window_focus_lost(event);
    if (event->is<sf::Event::FocusGained>())            return _internal_on_window_focus_gained(event);
    if (event->is<sf::Event::MouseEntered>())           return _internal_on_window_mouse_enter(event);
    if (event->is<sf::Event::MouseLeft>())              return _internal_on_window_mouse_leave(event);
    if (event->is<sf::Event::TextEntered>())            return _internal_on_text_entered(event);
    if (event->is<sf::Event::KeyPressed>())             return _internal_on_key_press(event);
    if (event->is<sf::Event::KeyReleased>())            return _internal_on_key_release(event);
    if (event->is<sf::Event::MouseWheelScrolled>())     return _internal_on_mouse_wheel_scroll(event);
    if (event->is<sf::Event::MouseButtonPressed>())     return _internal_on_mouse_click(event);
    if (event->is<sf::Event::MouseButtonReleased>())    return _internal_on_mouse_release(event);
    if (event->is<sf::Event::MouseMoved>())             return _internal_on_mouse_move(event);
    if (event->is<sf::Event::JoystickButtonPressed>())  return _internal_on_joystick_button_press(event);
    if (event->is<sf::Event::JoystickButtonReleased>()) return _internal_on_joystick_button_release(event);
    if (event->is<sf::Event::JoystickMoved>())          return _internal_on_joystick_move(event);
    if (event->is<sf::Event::JoystickConnected>())      return _internal_on_joystick_connect(event);
    if (event->is<sf::Event::JoystickDisconnected>())   return _internal_on_joystick_disconnect(event);
    if (event->is<sf::Event::TouchBegan>())             return _internal_on_touch_begin(event);
    if (event->is<sf::Event::TouchMoved>())             return _internal_on_touch_move(event);
    if (event->is<sf::Event::TouchEnded>())             return _internal_on_touch_end(event);
    if (event->is<sf::Event::SensorChanged>())          return _internal_on_sensor_change(event);
    return false;
}

bool nd::Widget::_internal_on_window_closed(const std::optional<sf::Event> event) {
    if (_on_window_closed) { return _on_window_closed(event); }
    return false;
}

bool nd::Widget::_internal_on_window_resized(const std::optional<sf::Event> event) {
    if (_on_window_resized) { return _on_window_resized(event); }
    return false;
}

bool nd::Widget::_internal_on_window_focus_lost(const std::optional<sf::Event> event) {
    if (_on_window_focus_lost) { return _on_window_focus_lost(event); }
    return false;
}

bool nd::Widget::_internal_on_window_focus_gained(const std::optional<sf::Event> event) {
    if (_on_window_focus_gained) { return _on_window_focus_gained(event); }
    return false;
}

bool nd::Widget::_internal_on_window_mouse_enter(const std::optional<sf::Event> event) {
    if (_on_window_mouse_enter) { return _on_window_mouse_enter(event); }
    return false;
}

bool nd::Widget::_internal_on_window_mouse_leave(const std::optional<sf::Event> event) {
    if (_on_window_mouse_leave) { return _on_window_mouse_leave(event); }
    return false;
}

bool nd::Widget::_internal_on_text_entered(const std::optional<sf::Event> event) {
    if (_on_text_entered) { return _on_text_entered(event); }
    return false;
}

bool nd::Widget::_internal_on_key_press(const std::optional<sf::Event> event) {
    if (_on_key_press) { return _on_key_press(event); }
    return false;
}

bool nd::Widget::_internal_on_key_release(const std::optional<sf::Event> event) {
    if (_on_key_release) { return _on_key_release(event); }
    return false;
}

bool nd::Widget::_internal_on_mouse_wheel_scroll(const std::optional<sf::Event> event) {
    if (_on_mouse_wheel_scroll) { return _on_mouse_wheel_scroll(event); }
    return false;
}

bool nd::Widget::_internal_on_mouse_click(const std::optional<sf::Event> event) {
    if (!_on_mouse_click) return false;
    const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>();
    if (mouseButton && INTERSECTS_MOUSE(mouseButton->position))
        return _on_mouse_click(event);
    return false;
}

bool nd::Widget::_internal_on_mouse_release(const std::optional<sf::Event> event) {
    if (!_on_mouse_release) return false;
    const auto* mouseButton = event->getIf<sf::Event::MouseButtonReleased>();
    if (mouseButton && INTERSECTS_MOUSE(mouseButton->position))
        return _on_mouse_release(event);
    return false;
}

bool nd::Widget::_internal_on_mouse_move(const std::optional<sf::Event> event) {
    if (!_on_mouse_move) return false;
    const auto* mouseMove = event->getIf<sf::Event::MouseMoved>();
    if (mouseMove && INTERSECTS_MOUSE(mouseMove->position))
        return _on_mouse_move(event);
    return false;
}

bool nd::Widget::_internal_on_joystick_button_press(const std::optional<sf::Event> event) {
    if (_on_joystick_button_press) { return _on_joystick_button_press(event); }
    return false;
}

bool nd::Widget::_internal_on_joystick_button_release(const std::optional<sf::Event> event) {
    if (_on_joystick_button_release) { return _on_joystick_button_release(event); }
    return false;
}

bool nd::Widget::_internal_on_joystick_move(const std::optional<sf::Event> event) {
    if (_on_joystick_move) { return _on_joystick_move(event); }
    return false;
}

bool nd::Widget::_internal_on_joystick_connect(const std::optional<sf::Event> event) {
    if (_on_joystick_connect) { return _on_joystick_connect(event); }
    return false;
}

bool nd::Widget::_internal_on_joystick_disconnect(const std::optional<sf::Event> event) {
    if (_on_joystick_disconnect) { return _on_joystick_disconnect(event); }
    return false;
}

bool nd::Widget::_internal_on_touch_begin(const std::optional<sf::Event> event) {
    if (_on_touch_begin) { return _on_touch_begin(event); }
    return false;
}

bool nd::Widget::_internal_on_touch_move(const std::optional<sf::Event> event) {
    if (_on_touch_move) { return _on_touch_move(event); }
    return false;
}

bool nd::Widget::_internal_on_touch_end(const std::optional<sf::Event> event) {
    if (_on_touch_end) { return _on_touch_end(event); }
    return false;
}

bool nd::Widget::_internal_on_sensor_change(const std::optional<sf::Event> event) {
    if (_on_sensor_change) { return _on_sensor_change(event); }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
