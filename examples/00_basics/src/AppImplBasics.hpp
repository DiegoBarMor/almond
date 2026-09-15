#pragma once
#include "../almond.hpp"
#include "CustomWidget.hpp"

class AppImplBasics : public nd::App {
public:
    AppImplBasics(sf::RenderWindow& window) : nd::App(window) {}
    bool callback_key_press(const nd::Event& event);

protected:
    void _on_init() override;
    void _on_create() override;
};
