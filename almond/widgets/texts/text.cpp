#include "text.hpp"

// -----------------------------------------------------------------------------
bool nd::Text::set_spec(std::string key, std::string raw_value) { // FUNC@set_spec
    if (key == "T" || key == "TEXT") {
        _text_str = raw_value;
        __update_sfml_text();
        return true;
    }
    if (key == "FS" || key == "FONT_SIZE") {
        __font_size = std::stoi(raw_value);
        __update_sfml_text();
        return true;
    }
    if (key == "FC" || key == "FONT_COLOR") {
        _font_color = nd::ParserStrings::str2color(raw_value);
        __update_sfml_text();
        return true;
    }
    return nd::Widget::set_spec(key, raw_value);
} // END@set_spec


// -----------------------------------------------------------------------------
void nd::Text::build() { // FUNC@build
    nd::Widget::build();
    __update_sfml_text();

    sf::Vector2f pos = _pos;
    sf::FloatRect bounds = _text_obj.getLocalBounds();

    // Center the text
    if (_size.x > bounds.size.x) { pos.x += (_size.x - bounds.size.x) / 2.0f; }
    if (_size.y > bounds.size.y) { pos.y += (_size.y - bounds.size.y) / 2.0f; }

    _text_obj.setPosition(pos);
} // END@build


// -----------------------------------------------------------------------------
void nd::Text::draw(sf::RenderWindow& window) { // FUNC@draw
    window.draw(_shape);
    window.draw(_text_obj);
} // END@draw


// -----------------------------------------------------------------------------
void nd::Text::__update_sfml_text() { // FUNC@__update_sfml_text
    _text_obj.setFont(font);
    _text_obj.setString(_text_str);
    _text_obj.setCharacterSize(__font_size);
    _text_obj.setFillColor(_font_color);
} // END@__update_sfml_text


// -----------------------------------------------------------------------------
