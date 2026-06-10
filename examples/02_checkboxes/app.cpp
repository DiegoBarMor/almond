#include <SFML/Graphics.hpp>

#include "src/AppImplCheckBoxes.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "ALMOND Example - CheckBoxes");
    window.setFramerateLimit(60);

    AppImplCheckBoxes gui = AppImplCheckBoxes(window);
    gui.setup("layout.ndg");

    ////// Callbacks
    nd::Widget* root = gui.get_widget("root");
    root->link_on_window_closed([&gui](sf::Event event) {
        gui.get_window().close();
        return true;
    });
    root->link_on_key_press([&gui](sf::Event event) {
        if (event.key.code == sf::Keyboard::Escape) {
            gui.get_window().close();
            return true;
        }
        return false;
    });

    ////// Main loop
    while (window.isOpen()) {
        gui.manage_events();
        window.clear(sf::Color::Black);
        gui.draw();
        window.display();
    }
    return 0;
}
