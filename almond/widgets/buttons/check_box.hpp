#pragma once
#include "toggleable_button.hpp"

namespace nd {
class CheckBox : public ToggleableButton {
public:
    CheckBox() : ToggleableButton() {}
    CheckBox* clone() override { return new CheckBox(); }

    void build() override; // HEAD@build
    void draw(sf::RenderWindow& window) override; // HEAD@draw

protected:
    void _internal_on_toggle() override; // HEAD@_internal_on_toggle

private:
    sf::VertexArray __check_mark = sf::VertexArray(sf::PrimitiveType::TriangleStrip, 6);
};
}
