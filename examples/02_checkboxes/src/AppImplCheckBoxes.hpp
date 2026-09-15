#pragma once
#include "../almond.hpp"

class AppImplCheckBoxes : public nd::App {
public:
    AppImplCheckBoxes(sf::RenderWindow& window) : nd::App(window) {}
    bool callback_key_press(const nd::Event& event);

protected:
    void _on_init() override;
    void _on_create() override;
    void _on_build() override;
};
