#include <SFML/Graphics.hpp>

#include "almond.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "ALMOND Example 01 - Buttons");
    window.setFramerateLimit(60);

    nd::App app = nd::App(window);
    app.setup("layout.ndg");

    ////// Callbacks
    app.link_on_event([&app](const nd::Event& event) {
        switch (event.generic.type) {
        case nd::EventType::CLOSED:
            app.get_window().close();
            return true;
        case nd::EventType::KEY_PRESSED:
            if (event.key_pressed.code == sf::Keyboard::Key::Escape) {
                app.get_window().close();
                return true;
            }
            return false;
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
