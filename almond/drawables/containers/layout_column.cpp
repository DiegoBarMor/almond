#include "layout_column.hpp"

// -----------------------------------------------------------------------------
void nd::LayoutColumn::build() { // FUNC@build
    _init_shape();
    int i = 0;
    float
        sx = _size.x - 2.0f*get_padding(),
        px = _pos.x + get_padding(),
        py = _pos.y,
        sy = 0.0f,
        weight_children = 0.f;

    for (auto& child : _children) {
        weight_children += child->get_weight();
    }
    if (weight_children < 1.0f) { weight_children = 1.0f; }

    for (auto& child : _children) {
        py += sy + _calc_offset_pos(i);
        sy = child->get_weight() / weight_children * _size.y - _calc_offset_size(i);
        child->set_pos(sf::Vector2f(px, py));
        child->set_size(sf::Vector2f(sx, sy));
        child->build();
        i++;
    }
} // END@build


// -----------------------------------------------------------------------------
