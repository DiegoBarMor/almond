#pragma once
#include "../widget.hpp"
#include "font_crimson_roman.hpp"

namespace nd {
class Text : public Widget {
public:
    Text(sf::Font font) : Widget(), font(font), _text_obj(sf::Text(font)) {}
    std::unique_ptr<Widget> clone() const override {
        return std::make_unique<Text>(font);
    }

    bool set_spec(std::string key, std::string raw_value) override; // HEAD@set_spec
    void build() override; // HEAD@build
    void draw(sf::RenderWindow& window) override; // HEAD@draw

    void set_text_str  (const std::string& text)  { _text_str = text;    }
    void set_font_size (unsigned int size)        { __font_size = size;  }
    void set_font_color(const sf::Color& color)   { _font_color = color; }

    const std::string& get_text_str  () const { return _text_str;   }
    unsigned int       get_font_size () const { return __font_size; }
    const sf::Color&   get_font_color() const { return _font_color; }

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
