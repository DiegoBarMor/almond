#pragma once
#include "../../../src/almond/App.hpp"
#include "CustomWidget.hpp"

class AppImplBasics : public nd::App {
public:
    AppImplBasics(sf::RenderWindow& window) : nd::App(window) {}

protected:
    void _on_init() override;
    void _on_create() override;
};
