#pragma once
#include "button_primitive.hpp"
#include "../texts/text.hpp"

namespace nd {
class LabeledButton : public ButtonPrimitive {
public:
    LabeledButton(sf::Font font) : ButtonPrimitive(), __text_widget(nd::Text(font)) {}
    std::unique_ptr<Widget> clone() const override {
        return std::make_unique<LabeledButton>(__text_widget.font);
    }

    bool set_spec(std::string key, std::string raw_value) override; // HEAD@set_spec
    void build() override; // HEAD@build
    void draw(sf::RenderWindow& window) override; // HEAD@draw

    nd::Text& get_text_widget() { return __text_widget; }

private:
    nd::Text __text_widget;
};
}
