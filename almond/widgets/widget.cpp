#include "widget.hpp"

// -----------------------------------------------------------------------------
bool nd::Widget::set_spec(std::string key, std::string raw_value) { // FUNC@set_spec
    if (key == "W" || key == "WEIGHT") {
        __weight = nd::ParserStrings::str2float(raw_value);
        return true;
    }
    if (key == "BG" || key == "BG_COLOR") {
        _bg_color = nd::ParserStrings::str2color(raw_value);
        return true;
    }
    return false;
} // END@set_spec


// -----------------------------------------------------------------------------
void nd::Widget::add_child(std::shared_ptr<Widget> child) { // FUNC@add_child
    std::cerr << "Can't add child to non-container widget" << std::endl;
} // END@add_child


// -----------------------------------------------------------------------------
void nd::Widget::build() { // FUNC@build
    _init_shape();
} // END@build


// -----------------------------------------------------------------------------
bool nd::Widget::handle_event(const nd::Event& event) { // FUNC@handle_event
    return _on_event ? _on_event(event) : false;
} // END@handle_event


// -----------------------------------------------------------------------------
void nd::Widget::draw(sf::RenderWindow& window) { // FUNC@draw
    window.draw(_shape);
} // END@draw


// -----------------------------------------------------------------------------
void nd::Widget::set_bg_color(const sf::Color& color) { // FUNC@set_bg_color
    _bg_color = color;
    _shape.setFillColor(color);
} // END@set_bg_color


// -----------------------------------------------------------------------------
bool nd::Widget::contains_point(sf::Vector2i point) { // FUNC@contains_point
    sf::Vector2f point_f((float)point.x, (float)point.y);
    return _shape.getGlobalBounds().contains(point_f);
} // END@contains_point


// -----------------------------------------------------------------------------
void nd::Widget::force_widget_square() { // FUNC@force_widget_square
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
} // END@force_widget_square


// -----------------------------------------------------------------------------
void nd::Widget::_init_shape() { // FUNC@_init_shape
    _shape.setSize(_size);
    _shape.setPosition(_pos);
    _shape.setFillColor(get_bg_color());
} // END@_init_shape


// -----------------------------------------------------------------------------
