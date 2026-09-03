#include "radio_button.hpp"

// -----------------------------------------------------------------------------
bool nd::RadioButton::set_spec(std::string key, std::string raw_value) { // FUNC@set_spec
    if (key == "GRP" || key == "GROUP") {
        __group_id = raw_value;
        return true;
    }
    return nd::ToggleableButton::set_spec(key, raw_value);
} // END@set_spec


// -----------------------------------------------------------------------------
void nd::RadioButton::build() { // FUNC@build
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
} // END@build


// -----------------------------------------------------------------------------
void nd::RadioButton::draw(sf::RenderWindow& window) { // FUNC@draw
    nd::ToggleableButton::draw(window);
    if (_checked) window.draw(__check_mark);
} // END@draw


// -----------------------------------------------------------------------------
void nd::RadioButton::add_to_group(RadioButtonGroup* group) { // FUNC@add_to_group
    if (group == nullptr) return;

    __group = group;
    __idx_in_group = (int)(group->buttons.size());
    if (_checked) {
        group->selected_idx = __idx_in_group;
        _checked = false;
    }
    group->buttons.push_back(this);
} // END@add_to_group


// -----------------------------------------------------------------------------
bool nd::RadioButton::_on_mouse_button_pressed(const nd::Event& event) { // FUNC@_on_mouse_button_pressed
    if (_checked || __group == nullptr) return false;

    if (contains_point(event.mouse_button_released.position)) {
        set_checked(true);
        __group->buttons[__group->selected_idx]->set_checked(false);
        __group->selected_idx = __idx_in_group;
        if (_on_toggle) {
            bool consumed = _on_toggle(event);
            if (consumed) return true;
        }
    }
    return nd::ButtonPrimitive::_on_mouse_button_pressed(event);
} // END@_on_mouse_button_pressed


// -----------------------------------------------------------------------------
