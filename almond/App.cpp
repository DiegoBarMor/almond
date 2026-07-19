#include "App.hpp"

void nd::App::setup(const std::string &filename, sf::Vector2f pos, sf::Vector2f size) {
    if (size == sf::Vector2f(0, 0)) {
        size = sf::Vector2f((float)__window.getSize().x, (float)__window.getSize().y);
    }

    _on_init();

    __create(filename);
    _on_create();

    __build(pos, size);
    _on_build();
}

nd::Widget* nd::App::get_widget(std::string id) {
    return _widget_manager.get_widget_by_id(id);
}

void nd::App::manage_events() {
    if (__root == nullptr) return;
    while (const std::optional event = __window.pollEvent()) {
        if (_internal_manage_event(event)) continue;
        __root->handle_event(event);
    }
}

void nd::App::draw() {
    if (__root == nullptr) return;
    __root->draw(__window);
}

void nd::App::__create(const std::string &filename) {
    if (filename != "") {
        __root = nd::NDGParser(_widget_manager).parse(filename);
        if (__root == nullptr) {
            std::cerr << "Failed to parse NDG file: " << filename << std::endl;
            std::cout << "Creating empty Container as the root widget." << std::endl;
            __root = new nd::Container();
        }
    } else {
        std::cout << "No NDG file provided. Creating empty Container as the root widget." << std::endl;
        __root = new nd::Container();
    }
    _widget_manager.set_id(__root, "root");
}

void nd::App::__build(sf::Vector2f pos, sf::Vector2f size) {
    __root->set_pos(pos);
    __root->set_size(size);
    __root->build();
}
