#include "Buttons.hpp"

////////////////////////////////////////////////////////////////////////////////

bool nd::ButtonPrimitive::set_spec(std::string key, std::string raw_value) {
    if (key == "E" || key == "ENABLED") {
        set_enabled(nd::parse_bool_string(raw_value));
        return true;
    }
    if (key == "BGI" || key == "BG_IDLE") {
        __bg_idle = nd::parse_color_string(raw_value);
        return true;
    }
    if (key == "BGH" || key == "BG_HOVER") {
        __bg_hover = nd::parse_color_string(raw_value);
        return true;
    }
    if (key == "BGP" || key == "BG_PRESSED") {
        __bg_pressed = nd::parse_color_string(raw_value);
        return true;
    }
    if (key == "BGD" || key == "BG_DISABLED") {
        __bg_disabled = nd::parse_color_string(raw_value);
        return true;
    }
    return nd::Widget::set_spec(key, raw_value);
}

void nd::ButtonPrimitive::build() {
    __set_state(_state); // this ensures that the proper colors are being used
    nd::Widget::build();
}

void nd::ButtonPrimitive::set_enabled(bool enabled) {
    __set_state(enabled ? State::IDLE : State::DISABLED);
}

bool nd::ButtonPrimitive::get_enabled() {
    return _state != State::DISABLED;
}

bool nd::ButtonPrimitive::_internal_on_mouse_click(sf::Event event) {
    if (_state == State::DISABLED) return false;
    if (!INTERSECTS_MOUSE(event.mouseButton)) return false;
    __set_state(State::PRESSED);
    if (!_on_mouse_click) return false;
    return _on_mouse_click(event);
}

bool nd::ButtonPrimitive::_internal_on_mouse_release(sf::Event event) {
    if (_state == State::DISABLED) return false;
    if (INTERSECTS_MOUSE(event.mouseButton)) {
        // update the button state and carry out _on_mouse_release as usual
        __set_state(State::HOVER);
        if (!_on_mouse_release) return false;
        return _on_mouse_release(event);
    }
    if (_state == State::PRESSED) {
        // mouse was pressed on the button but released outside its bounds
        // the button state is updated, but _on_mouse_release is not called
        // basically, the on_release action is cancelled
        __set_state(State::IDLE);
    }
    return false;
}

bool nd::ButtonPrimitive::_internal_on_mouse_move(sf::Event event) {
    if (_state == State::DISABLED) return false;
    if (INTERSECTS_MOUSE(event.mouseMove)) {
        if (_state == State::IDLE) {
            __set_state(State::HOVER);
        }
        if (!_on_mouse_move) return false;
        return _on_mouse_move(event);
    }
    if (_state == State::HOVER) {
        __set_state(State::IDLE);
    }
    return false;
}

void nd::ButtonPrimitive::__set_state(State state) {
    _state = state;
    switch (state) {
        case State::IDLE:
            _bg_color = __bg_idle; break;
        case State::HOVER:
            _bg_color = __bg_hover; break;
        case State::PRESSED:
            _bg_color = __bg_pressed; break;
        case State::DISABLED:
            _bg_color = __bg_disabled; break;
    }
    _shape.setFillColor(_bg_color);
}

////////////////////////////////////////////////////////////////////////////////

bool nd::LabeledButton::set_spec(std::string key, std::string raw_value) {
    if (nd::ButtonPrimitive::set_spec(key, raw_value))
        return true;
    return __text_widget.set_spec(key, raw_value);
}

void nd::LabeledButton::build() {
    nd::ButtonPrimitive::build();
    __text_widget.set_pos(get_pos());
    __text_widget.set_size(get_size());
    __text_widget.build();
}

void nd::LabeledButton::draw(sf::RenderWindow& window) {
    nd::ButtonPrimitive::draw(window);
    __text_widget.draw(window);
}

////////////////////////////////////////////////////////////////////////////////

bool nd::ToggleableButton::set_spec(std::string key, std::string raw_value) {
    if (key == "CHK" || key == "CHECKED") {
        set_checked(nd::parse_bool_string(raw_value));
        return true;
    }
    if (key == "FGM" || key == "COLOR_MARK") {
        _color_mark = nd::parse_color_string(raw_value);
        return true;
    }
    if (key == "OTH" || key == "OUTLINE_THICKNESS") {
        _outline_thickness = nd::parse_ratio_string(raw_value);
        return true;
    }
    return nd::ButtonPrimitive::set_spec(key, raw_value);
}

void nd::ToggleableButton::build() {
    set_checked(_checked);
    force_widget_square();
    nd::ButtonPrimitive::build();

    sf::Vector2f
        size = (1.0f-_outline_thickness)*_size,
        pos = _pos + (_outline_thickness/2.0f)*_size;
    _shape_overlay.setSize(size);
    _shape_overlay.setPosition(pos);
    _shape_overlay.setFillColor(_color_overlay);
}

bool nd::ToggleableButton::handle_event(sf::Event event) {
    if (_state == State::DISABLED) return false;
    if (
        event.type == sf::Event::MouseButtonReleased &&
        INTERSECTS_MOUSE(event.mouseButton)
    ) {
        _internal_on_toggle();
    }
    return nd::ButtonPrimitive::handle_event(event);
}

void nd::ToggleableButton::draw(sf::RenderWindow& window) {
    nd::ButtonPrimitive::draw(window);
    window.draw(_shape_overlay);
}

////////////////////////////////////////////////////////////////////////////////

void nd::CheckBox::build() {
    nd::ToggleableButton::build();
    sf::Vector2f
        size = _shape_overlay.getSize(),
        pos = _shape_overlay.getPosition();
    float
        x0 = pos.x + 0.09f*size.x,
        x1 = pos.x + 0.25f*size.x,
        x2 = pos.x + 0.42f*size.x,
        x3 = pos.x + 0.78f*size.x,
        x4 = pos.x + 0.94f*size.x,

        y0 = pos.y + 0.13f*size.y,
        y1 = pos.y + 0.43f*size.y,
        y2 = pos.y + 0.66f*size.y,
        y3 = pos.y + 0.89f*size.y;

    __check_mark[0].position = sf::Vector2f(x1, y1);
    __check_mark[1].position = sf::Vector2f(x0, y1);
    __check_mark[2].position = sf::Vector2f(x2, y2);
    __check_mark[3].position = sf::Vector2f(x2, y3);
    __check_mark[4].position = sf::Vector2f(x3, y0);
    __check_mark[5].position = sf::Vector2f(x4, y0);
    __check_mark[0].color = _color_mark;
    __check_mark[1].color = _color_mark;
    __check_mark[2].color = _color_mark;
    __check_mark[3].color = _color_mark;
    __check_mark[4].color = _color_mark;
    __check_mark[5].color = _color_mark;
}

void nd::CheckBox::draw(sf::RenderWindow& window) {
    nd::ToggleableButton::draw(window);
    if (_checked) window.draw(__check_mark);
}

void nd::CheckBox::_internal_on_toggle() {
    set_checked(!_checked);
    if (_on_toggle) _on_toggle();
}

////////////////////////////////////////////////////////////////////////////////

bool nd::RadioButton::__is_first_build = true;
std::vector<nd::RadioButton*>
    nd::RadioButton::__list_radiobuttons = {};
std::unordered_map<std::string, nd::RadioButton::RadioButtonGroup*>
    nd::RadioButton::__table_groups = {};

nd::RadioButton* nd::RadioButton::clone() {
    // this is done here and not in the constructor
    // so that the prototype isn't added to the list
    RadioButton* rb = new RadioButton();
    __list_radiobuttons.push_back(rb);
    return rb;
}

bool nd::RadioButton::set_spec(std::string key, std::string raw_value) {
    if (key == "GRP" || key == "GROUP") {
        __group_id = raw_value;
        return true;
    }
    return nd::ToggleableButton::set_spec(key, raw_value);
}

void nd::RadioButton::build() {
    if (__is_first_build) __first_build();
    nd::ToggleableButton::build();
    sf::Vector2f
        size = _shape_overlay.getSize(),
        pos = _shape_overlay.getPosition();
    float
        radius = __check_mark_ratio*size.x/2.0f,
        pos_offset = (1.0f-__check_mark_ratio)*size.x/2.0f;
    pos.x += pos_offset;
    pos.y += pos_offset;

    __check_mark.setPosition(pos);
    __check_mark.setRadius(radius);
    __check_mark.setFillColor(_color_mark);
}

void nd::RadioButton::draw(sf::RenderWindow& window) {
    nd::ToggleableButton::draw(window);
    if (_checked) window.draw(__check_mark);
}

void nd::RadioButton::_internal_on_toggle() {
    if (_checked || __group == nullptr) return;
    set_checked(true);
    __group->buttons[__group->selected_idx]->set_checked(false);
    __group->selected_idx = __idx_in_group;
    if (_on_toggle) _on_toggle();
}

void nd::RadioButton::__first_build() {
    __is_first_build = false;

    RadioButtonGroup* group;
    for (auto rb : __list_radiobuttons) {
        group = __table_groups[rb->__group_id];
        if (group == nullptr) {
            group = new RadioButtonGroup();
            __table_groups[rb->__group_id] = group;
        }
        rb->__group = group;
        rb->__idx_in_group = (int)(group->buttons.size());
        if (rb->_checked) {
            group->selected_idx = rb->__idx_in_group;
            rb->_checked = false;
        }
        group->buttons.push_back(rb);
    }

    // this list is no longer needed
    __list_radiobuttons.clear();
    __list_radiobuttons.shrink_to_fit();

    for (auto& [group_id, group] : __table_groups) {
        if (group->selected_idx == -1) group->selected_idx = 0;
        group->buttons[group->selected_idx]->_checked = true;
    }
}

////////////////////////////////////////////////////////////////////////////////
