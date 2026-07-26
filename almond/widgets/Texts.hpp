#pragma once
#include "Widget.hpp"
#include "../assets/font_crimson_roman.hpp"

namespace nd {
////////////////////////////////////////////////////////////////////////////////

class Text : public Widget {
public:
    // m.0a (Construction methods)
    Text(sf::Font font) : Widget(), font(font), _text_obj(sf::Text(font)) {}
    Text* clone() override { return new Text(font); }

    // m.0c (Lifecycle methods - SABHD)
    bool set_spec(std::string key, std::string raw_value) override;
    void build() override;
    void draw(sf::RenderWindow& window) override;

    // m.0d (Setters/Getters for the spec fields)
    void         set_text_str  (std::string text)  { _text_str = text;    }
    void         set_font_size (unsigned int size) { __font_size = size;  }
    void         set_font_color(sf::Color color)   { _font_color = color; }
    std::string  get_text_str  ()                  { return _text_str;    }
    unsigned int get_font_size ()                  { return __font_size;  }
    sf::Color    get_font_color()                  { return _font_color;  }

    // d.0d (Other fields)
    sf::Font font = sf::Font();

protected:
    // d.1b (Spec fields)
    std::string _text_str = "";
    sf::Color _font_color = sf::Color::White;

    // d.1d (Other fields)
    sf::Text _text_obj = sf::Text(font);

private:
    // m.2a (Internal functionalities)
    void __update_sfml_text();

    // d.2b (Spec fields)
    unsigned int __font_size = 20;
};

////////////////////////////////////////////////////////////////////////////////

class TextInput : public Text {
public:
    // m.0a (Construction methods)
    TextInput(sf::Font font);
    TextInput* clone() override { return new TextInput(font); }

    // m.0c (Lifecycle methods - SABHD)
    bool set_spec(std::string key, std::string raw_value) override;
    void build() override;
    void draw(sf::RenderWindow& window) override;

    // m.0d (Setters/Getters for the spec fields)
    void        set_hint_str  (std::string hint) { __hint_str = hint;    }
    void        set_hint_color(sf::Color color)  { __hint_color = color; }
    std::string get_hint_str  ()                 { return __hint_str;    }
    sf::Color   get_hint_color()                 { return __hint_color;  }

protected:
    // m.1b (Callback wrappers)
    bool _internal_on_mouse_release(const std::optional<sf::Event> event) override;
    bool _internal_on_text_entered (const std::optional<sf::Event> event) override;

    // d.1b (Spec fields)
    float _outline_thickness = 0.1f; // ratio (0.0f-1.0f) [WIP]

private:
    // d.2b (Spec fields)
    std::string __hint_str = "";
    bool __is_focused = false;

    // d.2c (Other fields)
    sf::Color __hint_color = sf::Color(100, 100, 100, 255);
    sf::Color __color_overlay_idle = sf::Color(200, 200, 200, 200);
    sf::Color __color_overlay_focused = sf::Color(255, 255, 255, 200);
    sf::RectangleShape __shape_overlay = sf::RectangleShape();
};

////////////////////////////////////////////////////////////////////////////////
}
