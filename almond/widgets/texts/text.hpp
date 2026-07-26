#pragma once
#include "../Widget.hpp"
#include "font_crimson_roman.hpp"

namespace nd {
class Text : public Widget {
public:
    Text(sf::Font font) : Widget(), font(font), _text_obj(sf::Text(font)) {}
    Text* clone() override { return new Text(font); }

    bool set_spec(std::string key, std::string raw_value) override; // HEAD@set_spec
    void build() override; // HEAD@build
    void draw(sf::RenderWindow& window) override; // HEAD@draw

    void         set_text_str  (std::string text)  { _text_str = text;    }
    void         set_font_size (unsigned int size) { __font_size = size;  }
    void         set_font_color(sf::Color color)   { _font_color = color; }
    std::string  get_text_str  ()                  { return _text_str;    }
    unsigned int get_font_size ()                  { return __font_size;  }
    sf::Color    get_font_color()                  { return _font_color;  }

    sf::Font font = sf::Font();

protected:
    std::string _text_str = "";
    sf::Color _font_color = sf::Color::White;

    sf::Text _text_obj = sf::Text(font);

private:
    void __update_sfml_text(); // HEAD@__update_sfml_text

    unsigned int __font_size = 20;
};
}
