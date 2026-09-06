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
void nd::Container::add_child(std::shared_ptr<Widget> child) { // FUNC@add_child
    if (child == nullptr) {
        std::cerr << "Can't add null child to container" << std::endl;
        return;
    }
    child->set_parent(this);
    _children.push_back(child);
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
