#pragma once
#include "button_primitive.hpp"
#include "../Texts.hpp"

namespace nd {
class LabeledButton : public ButtonPrimitive {
public:
    LabeledButton(sf::Font font) : ButtonPrimitive(), __text_widget(nd::Text(font)) {}
    LabeledButton* clone() override { return new LabeledButton(__text_widget.font); }

    bool set_spec(std::string key, std::string raw_value) override; // HEAD@set_spec
    void build() override; // HEAD@build
    void draw(sf::RenderWindow& window) override; // HEAD@draw

    nd::Text& get_text_widget() { return __text_widget; }

private:
    nd::Text __text_widget;
};
}
