#pragma once
#include "../../../src/almond/App.hpp"

class AppImplCheckBoxes : public nd::App {
public:
    AppImplCheckBoxes(sf::RenderWindow& window) : nd::App(window) {}

protected:
    void _on_init() override;
    void _on_create() override;
    void _on_build() override;
};
