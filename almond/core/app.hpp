#pragma once
#include "widget_manager.hpp"
#include "../parsers/parser_ndg.hpp"

namespace nd {
class App {
public:
    App(sf::RenderWindow& window) : __window(window) {}
    void setup(
        const std::string& filename = "",
        sf::Vector2f pos = {0, 0}, sf::Vector2f size = {0, 0}
    ); // HEAD@setup

    // These methods are called by the client code when interacting with the GUI.
    sf::RenderWindow& get_window() { return __window; }
    nd::Widget* get_widget(std::string id); // HEAD@get_widget
    void manage_events(); // HEAD@manage_events
    void draw(); // HEAD@draw

protected:
    // Override this to link callbacks that could be handled "globally" by the App.
    // For example, closing the window when pressing the Escape key or handling the window resizing.
    virtual bool _internal_manage_event(const std::optional<sf::Event> event) { return false; }

    // Override this to add behaviour that should happen before creating the root widget.
    // For example, adding custom prototypes.
    virtual void _on_init() {};

    // Override this to add behaviour that should happen after the root widget is created and before building the widgets.
    // Linking widget callbacks could be done here.
    virtual void _on_create() {};

    // Override this to add behaviour that should happen after the widgets are built.
    // For example, setting the focus on a specific widget or post-processing of size/pos of some widgets.
    // Linking widget callbacks could be done here.
    virtual void _on_build() {};

    WidgetManager _widget_manager = WidgetManager();

private:
    void __create(const std::string& filename); // HEAD@__create
    void __build(sf::Vector2f pos, sf::Vector2f size); // HEAD@__build

    Widget* __root = nullptr;
    sf::RenderWindow& __window;
    sf::Vector2f __pos = {0, 0};
    sf::Vector2f __size = {0, 0};
};
}
