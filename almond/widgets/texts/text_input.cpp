#include "text_input.hpp"

// -----------------------------------------------------------------------------
nd::TextInput::TextInput(sf::Font font) : Text(font) { // FUNC@TextInput
    _font_color = sf::Color::Black;
    set_bg_color(sf::Color(0x4A4A4AFF));
} // END@TextInput


// -----------------------------------------------------------------------------
bool nd::TextInput::set_spec(std::string key, std::string raw_value) { // FUNC@set_spec
    if (key == "H" || key == "HINT") {
        __hint_str = raw_value;
        return true;
    }
    if (key == "HC" || key == "HINT_COLOR") {
        __hint_color = nd::ParserStrings::str2color(raw_value);
        return true;
    }
    return nd::Text::set_spec(key, raw_value);
} // END@set_spec


// -----------------------------------------------------------------------------
void nd::TextInput::build() { // FUNC@build
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
} // END@build


// -----------------------------------------------------------------------------
void nd::TextInput::draw(sf::RenderWindow& window) { // FUNC@draw
    window.draw(_shape);
    window.draw(__shape_overlay);
    window.draw(_text_obj);
} // END@draw


// -----------------------------------------------------------------------------
bool nd::TextInput::_internal_on_mouse_button_released(const std::optional<sf::Event> event) { // FUNC@_internal_on_mouse_button_released
    if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonReleased>()) {
        __is_focused = INTERSECTS_MOUSE(mouseButton->position);
    }
    build();
    if (!_on_mouse_button_released) return false;
    return _on_mouse_button_released(event);
} // END@_internal_on_mouse_button_released


// -----------------------------------------------------------------------------
bool nd::TextInput::_internal_on_text_entered(const std::optional<sf::Event> event) { // FUNC@_internal_on_text_entered
    if (!__is_focused) return false;

    const auto* text = event->getIf<sf::Event::TextEntered>();
    if (!text) return false;

    std::cout << text->unicode << std::endl; // [DEBUG]

    switch (text->unicode) {
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
        _text_str += sf::Clipboard::getString().toAnsiString();
        break;
    default:
        _text_str += text->unicode;
        break;
    }
    build();
    return nd::Text::_internal_on_text_entered(event);
} // END@_internal_on_text_entered


// -----------------------------------------------------------------------------
