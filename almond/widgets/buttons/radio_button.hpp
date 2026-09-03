#pragma once
#include "toggleable_button.hpp"

namespace nd {
class RadioButton : public ToggleableButton {
public:
    struct RadioButtonGroup {
        int selected_idx = -1;
        std::vector<RadioButton*> buttons = {};
    };

    RadioButton() : ToggleableButton() { }
    std::unique_ptr<Widget> clone() const override {
        return std::make_unique<RadioButton>();
    }

    bool set_spec(std::string key, std::string raw_value) override; // HEAD@set_spec
    void build() override; // HEAD@build
    void draw(sf::RenderWindow& window) override; // HEAD@draw

    const std::string& get_group_id() const { return __group_id; }

    void add_to_group(RadioButtonGroup* group); // HEAD@add_to_group

protected:
    bool _on_mouse_button_pressed(const nd::Event& event) override; // HEAD@_on_mouse_button_pressed

private:
    std::string __group_id = "";

    RadioButtonGroup* __group = nullptr;
    int __idx_in_group = -1;

    sf::CircleShape __check_mark = sf::CircleShape();
    float __check_mark_ratio = 0.5f; // ratio (0.0f-1.0f) of the marker's size to the button's size
};
}
