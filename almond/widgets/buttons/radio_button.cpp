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
void nd::RadioButton::first_build(std::vector<nd::RadioButton*> list_radiobuttons) { // FUNC@first_build
    std::unordered_map<std::string, nd::RadioButton::RadioButtonGroup*> table_groups = {};
    for (auto rb : list_radiobuttons) {
        RadioButtonGroup* group = table_groups[rb->__group_id];
        if (group == nullptr) {
            group = new RadioButtonGroup();
            table_groups[rb->__group_id] = group;
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
    list_radiobuttons.clear();
    list_radiobuttons.shrink_to_fit();

    for (auto& [group_id, group] : table_groups) {
        if (group->selected_idx == -1) group->selected_idx = 0;
        group->buttons[group->selected_idx]->_checked = true;
    }
} // END@first_build


// -----------------------------------------------------------------------------
void nd::RadioButton::_internal_on_toggle() { // FUNC@_internal_on_toggle
    if (_checked || __group == nullptr) return;
    set_checked(true);
    __group->buttons[__group->selected_idx]->set_checked(false);
    __group->selected_idx = __idx_in_group;
    if (_on_toggle) _on_toggle();
} // END@_internal_on_toggle


// -----------------------------------------------------------------------------
