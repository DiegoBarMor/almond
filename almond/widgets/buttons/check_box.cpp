#include "check_box.hpp"

// -----------------------------------------------------------------------------
void nd::CheckBox::build() { // FUNC@build
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
} // END@build


// -----------------------------------------------------------------------------
void nd::CheckBox::draw(sf::RenderWindow& window) { // FUNC@draw
    nd::ToggleableButton::draw(window);
    if (_checked) window.draw(__check_mark);
} // END@draw


// -----------------------------------------------------------------------------
void nd::CheckBox::_internal_on_toggle() { // FUNC@_internal_on_toggle
    set_checked(!_checked);
    if (_on_toggle) _on_toggle();
} // END@_internal_on_toggle


// -----------------------------------------------------------------------------
