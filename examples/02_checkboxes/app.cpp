#include <SFML/Graphics.hpp>

#include "src/AppImplCheckBoxes.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "ALMOND Example 02 - CheckBoxes");
    window.setFramerateLimit(60);

    AppImplCheckBoxes app = AppImplCheckBoxes(window);
    app.setup("layout.ndg");

    ////// Callbacks
    nd::EventManager& eman = app.get_event_manager();
    eman.add_on_closed([&app]() {
        app.get_window().close();
        return true;
    });
    eman.add_on_key_pressed([&app,&eman]() {
        if (eman.key_pressed_is(sf::Keyboard::Key::Escape)) {
            app.get_window().close();
            return true;
        }
        return false;
    });

    ////// Main loop
    while (window.isOpen()) {
        app.manage_events();
        window.clear(sf::Color::Black);
        app.draw();
        window.display();
    }
    return 0;
}
