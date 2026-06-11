#include "Texts.hpp"

sf::Font* nd::Text::__font = nullptr;

////////////////////////////////////////////////////////////////////////////////

nd::Text::Text() : nd::Widget() {
    if (__font == nullptr) {
        __font = new sf::Font();
        if (!__font->loadFromMemory(nd::tff_crimson_roman, nd::size_crimson_roman)) {
            std::cerr << "Error loading font" << std::endl;
            return;
        }
    }
}

bool nd::Text::set_spec(std::string key, std::string raw_value) {
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
        _font_color = nd::parse_color_string(raw_value);
        __update_sfml_text();
        return true;
    }
    return nd::Widget::set_spec(key, raw_value);
}

void nd::Text::build() {
    nd::Widget::build();
    __update_sfml_text();

    sf::Vector2f pos = _pos;
    sf::FloatRect bounds = _text_obj.getLocalBounds();

    // Center the text
    if (_size.x > bounds.width ) { pos.x += (_size.x - bounds.width ) / 2.0f; }
    if (_size.y > bounds.height) { pos.y += (_size.y - bounds.height) / 2.0f; }

    _text_obj.setPosition(pos);
}

void nd::Text::draw(sf::RenderWindow& window) {
    window.draw(_shape);
    window.draw(_text_obj);
}

void nd::Text::__update_sfml_text() {
    if (__font == nullptr) return;
    _text_obj.setFont(*__font);
    _text_obj.setString(_text_str);
    _text_obj.setCharacterSize(__font_size);
    _text_obj.setFillColor(_font_color);
}

////////////////////////////////////////////////////////////////////////////////
nd::TextInput::TextInput() : Text() {
    _font_color = sf::Color::Black;
    set_bg_color(sf::Color(0x4A4A4AFF));
}

bool nd::TextInput::set_spec(std::string key, std::string raw_value) {
    if (key == "H" || key == "HINT") {
        __hint_str = raw_value;
        return true;
    }
    if (key == "HC" || key == "HINT_COLOR") {
        __hint_color = nd::parse_color_string(raw_value);
        return true;
    }
    return nd::Text::set_spec(key, raw_value);
}

void nd::TextInput::build() {
    std::string temp_str = _text_str;
    sf::Color temp_color = _font_color;

    if (_text_str.empty()) {
        _text_str = __hint_str;
        _font_color = __hint_color;
    }
    nd::Text::build();
    _text_str = temp_str;
    _font_color = temp_color;

    sf::Vector2f
        size = (1.0f-_outline_thickness)*_size,
        pos = _pos + (_outline_thickness/2.0f)*_size;
    __shape_overlay.setSize(size);
    __shape_overlay.setPosition(pos);
    __shape_overlay.setFillColor(
        __is_focused ? __color_overlay_focused : __color_overlay_idle
    );
}

void nd::TextInput::draw(sf::RenderWindow& window) {
    window.draw(_shape);
    window.draw(__shape_overlay);
    window.draw(_text_obj);
}

bool nd::TextInput::_internal_on_mouse_release(sf::Event event) {
    __is_focused = INTERSECTS_MOUSE(event.mouseButton);
    build();
    if (!_on_mouse_release) return false;
    return _on_mouse_release(event);
}

bool nd::TextInput::_internal_on_text_entered(sf::Event event) {
    if (!__is_focused) return false;
    std::cout << event.text.unicode << std::endl; // [DEBUG]

    switch (event.text.unicode) {
    case 3:  // Ctrl+C (Copy)
        sf::Clipboard::setString(_text_str);
        break;
    case 8: // Backspace
        if (!_text_str.empty()) _text_str.pop_back();
        break;
    case 13:  // Enter
        _text_str += '\n';
        break;
    case 24: // Ctrl+X (Cut)
        sf::Clipboard::setString(_text_str);
        _text_str.clear();
        break;
    case 22: // Ctrl+V (Paste)
        _text_str += sf::Clipboard::getString();
        break;
    default:
        _text_str += event.text.unicode;
        break;
    }
    build();
    return nd::Text::_internal_on_text_entered(event);
}

////////////////////////////////////////////////////////////////////////////////
