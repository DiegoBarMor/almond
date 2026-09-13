#pragma once
#include "toggleable_button.hpp"

namespace nd {
class CheckBox : public ToggleableButton {
public:
    CheckBox() : ToggleableButton() {}
    std::unique_ptr<Widget> clone() const override {
        return std::make_unique<CheckBox>();
    }

    void build() override; // HEAD@build
    void draw(sf::RenderWindow& window) override; // HEAD@draw

private:
    sf::VertexArray __check_mark = sf::VertexArray(sf::PrimitiveType::TriangleStrip, 6);
};
}
