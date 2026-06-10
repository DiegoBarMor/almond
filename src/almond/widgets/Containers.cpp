#include "Containers.hpp"

////////////////////////////////////////////////////////////////////////////////

bool nd::Container::set_spec(std::string key, std::string raw_value) {
    if (key == "P" || key == "PADDING") {
        __padding = nd::parse_float_string(raw_value);
        return true;
    }
    if (key == "S" || key == "SPACING") {
        __spacing = nd::parse_float_string(raw_value);
        return true;
    }
    return nd::Widget::set_spec(key, raw_value);
}

void nd::Container::add_child(nd::Widget* child) {
    _children.push_back(child);
    child->set_parent(this);
    _num_children++;
}

void nd::Container::build() {
    _init_shape();
    for (auto &child : _children) {
        child->set_pos(_pos);
        child->set_size(_size);
        child->build();
    }
}

bool nd::Container::handle_event(sf::Event event) {
    for (auto &child : _children) {
        if (child->handle_event(event))
            return true; // event handled by child, no need to continue
    }
    // event not handled by children, now the container tries to handle it.
    // this implies that children can override the container's event handling
    return _internal_handle_event(event);
}

void nd::Container::draw(sf::RenderWindow& window) {
    window.draw(_shape);
    for (auto &child : _children) {
        child->draw(window);
    }
}

float nd::Container::_calc_offset_pos(int child_index) {
    if (child_index == 0) return __padding;
    return __spacing;
}

float nd::Container::_calc_offset_size(int child_index) {
    if (_num_children == 1) return 2.0f*__padding;
    if (child_index == 0 || child_index == _num_children - 1)
        return __padding + __spacing / 2.0f;
    return __spacing;
}

////////////////////////////////////////////////////////////////////////////////
void nd::RowLayout::build() {
    _init_shape();
    int i = 0;
    float
        sx = 0.0f,
        px = _pos.x,
        py = _pos.y + get_padding(),
        sy = _size.y - 2.0f*get_padding(),
        weight_children = 0.f;

    for (auto &child : _children) {
        weight_children += child->get_weight();
    }
    if (weight_children < 1.0f) { weight_children = 1.0f; }

    for (auto &child : _children) {
        px += sx + _calc_offset_pos(i);
        sx = child->get_weight() / weight_children * _size.x - _calc_offset_size(i);
        child->set_pos(sf::Vector2f(px, py));
        child->set_size(sf::Vector2f(sx, sy));
        child->build();
        i++;
    }
}

////////////////////////////////////////////////////////////////////////////////

void nd::ColumnLayout::build() {
    _init_shape();
    int i = 0;
    float
        sx = _size.x - 2.0f*get_padding(),
        px = _pos.x + get_padding(),
        py = _pos.y,
        sy = 0.0f,
        weight_children = 0.f;

    for (auto &child : _children) {
        weight_children += child->get_weight();
    }
    if (weight_children < 1.0f) { weight_children = 1.0f; }

    for (auto &child : _children) {
        py += sy + _calc_offset_pos(i);
        sy = child->get_weight() / weight_children * _size.y - _calc_offset_size(i);
        child->set_pos(sf::Vector2f(px, py));
        child->set_size(sf::Vector2f(sx, sy));
        child->build();
        i++;
    }
}

////////////////////////////////////////////////////////////////////////////////
