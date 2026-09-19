#include "layout_row.hpp"

// -----------------------------------------------------------------------------
void nd::LayoutRow::build() { // FUNC@build
    _init_shape();
    int i = 0;
    float
        sx = 0.0f,
        px = _pos.x,
        py = _pos.y + get_padding(),
        sy = _size.y - 2.0f*get_padding(),
        weight_children = 0.f;

    for (auto& child : _children) {
        weight_children += child->get_weight();
    }
    if (weight_children < 1.0f) { weight_children = 1.0f; }

    for (auto& child : _children) {
        px += sx + _calc_offset_pos(i);
        sx = child->get_weight() / weight_children * _size.x - _calc_offset_size(i);
        child->set_pos(sf::Vector2f(px, py));
        child->set_size(sf::Vector2f(sx, sy));
        child->build();
        i++;
    }
} // END@build


// -----------------------------------------------------------------------------
