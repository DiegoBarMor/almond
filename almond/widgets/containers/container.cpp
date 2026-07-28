#include "container.hpp"

// -----------------------------------------------------------------------------
bool nd::Container::set_spec(std::string key, std::string raw_value) { // FUNC@set_spec
    if (key == "P" || key == "PADDING") {
        __padding = nd::ParserStrings::str2float(raw_value);
        return true;
    }
    if (key == "S" || key == "SPACING") {
        __spacing = nd::ParserStrings::str2float(raw_value);
        return true;
    }
    return nd::Widget::set_spec(key, raw_value);
} // END@set_spec


// -----------------------------------------------------------------------------
void nd::Container::add_child(nd::Widget* child) { // FUNC@add_child
    _children.push_back(child);
    child->set_parent(this);
    _num_children++;
} // END@add_child


// -----------------------------------------------------------------------------
void nd::Container::build() { // FUNC@build
    _init_shape();
    for (auto& child : _children) {
        child->set_pos(_pos);
        child->set_size(_size);
        child->build();
    }
} // END@build


// -----------------------------------------------------------------------------
bool nd::Container::handle_event(const std::optional<sf::Event> event) { // FUNC@handle_event
    for (auto& child : _children) {
        if (child->handle_event(event))
            return true; // event handled by child, no need to continue
    }
    // event not handled by children, now the container tries to handle it.
    // this implies that children can override the container's event handling
    return _internal_handle_event(event);
} // END@handle_event


// -----------------------------------------------------------------------------
void nd::Container::draw(sf::RenderWindow& window) { // FUNC@draw
    window.draw(_shape);
    for (auto& child : _children) {
        child->draw(window);
    }
} // END@draw


// -----------------------------------------------------------------------------
float nd::Container::_calc_offset_pos(int child_index) { // FUNC@_calc_offset_pos
    if (child_index == 0) return __padding;
    return __spacing;
} // END@_calc_offset_pos


// -----------------------------------------------------------------------------
float nd::Container::_calc_offset_size(int child_index) { // FUNC@_calc_offset_size
    if (_num_children == 1) return 2.0f*__padding;
    if (child_index == 0 || child_index == _num_children - 1)
        return __padding + __spacing / 2.0f;
    return __spacing;
} // END@_calc_offset_size


// -----------------------------------------------------------------------------
