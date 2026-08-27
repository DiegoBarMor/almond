#include <SFML/Graphics.hpp>

#include "src/AppImplBasics.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "ALMOND Example 00 - Basics");
    window.setFramerateLimit(60);

    AppImplBasics app = AppImplBasics(window);
    app.setup("layout.ndg");

    ////// Callbacks
    nd::EventManager event_man = app.get_event_manager();
    event_man.add_on_closed([&app](const std::optional<sf::Event> event) {
        app.get_window().close();
        return true;
    });
    event_man.add_on_key_pressed([&app](const std::optional<sf::Event> event) {
        const auto* keyPress = event->getIf<sf::Event::KeyPressed>();
        if (keyPress && keyPress->code == sf::Keyboard::Key::Escape) {
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
