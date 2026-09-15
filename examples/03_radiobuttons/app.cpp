#include <SFML/Graphics.hpp>

#include "almond.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "ALMOND Example 03 - Radio Buttons");
    window.setFramerateLimit(60);

    nd::App app = nd::App(window);
    app.setup("layout.ndg");

    ////// Callbacks
    nd::EventManager& eman = app.get_event_manager();
    app.link_on_event([&app,&eman](const nd::Event& event) {
        switch (event.generic.type) {
        case nd::EventType::CLOSED:
            app.get_window().close();
            return true;
        case nd::EventType::KEY_PRESSED:
            if (eman.get_key_pressed().code == sf::Keyboard::Key::Escape) {
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
