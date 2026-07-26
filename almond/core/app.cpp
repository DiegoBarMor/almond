#include "app.hpp"

// -----------------------------------------------------------------------------
void nd::App::setup(const std::string& filename, sf::Vector2f pos, sf::Vector2f size) { // FUNC@setup
    if (size == sf::Vector2f(0, 0)) {
        size = sf::Vector2f((float)__window.getSize().x, (float)__window.getSize().y);
    }

    _on_init();

    __create(filename);
    _on_create();

    __build(pos, size);
    _on_build();
} // END@setup


// -----------------------------------------------------------------------------
nd::Widget* nd::App::get_widget(std::string id) { // FUNC@get_widget
    return _widget_manager.get_widget_by_id(id);
} // END@get_widget


// -----------------------------------------------------------------------------
void nd::App::manage_events() { // FUNC@manage_events
    if (__root == nullptr) return;
    while (const std::optional event = __window.pollEvent()) {
        if (_internal_manage_event(event)) continue;
        __root->handle_event(event);
    }
} // END@manage_events


// -----------------------------------------------------------------------------
void nd::App::draw() { // FUNC@draw
    if (__root == nullptr) return;
    __root->draw(__window);
} // END@draw


// -----------------------------------------------------------------------------
void nd::App::__create(const std::string& filename) { // FUNC@__create
    if (filename != "") {
        __root = nd::ParserNDG(_widget_manager).parse(filename);
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
} // END@__create


// -----------------------------------------------------------------------------
void nd::App::__build(sf::Vector2f pos, sf::Vector2f size) { // FUNC@__build
    __root->set_pos(pos);
    __root->set_size(size);
    __root->build();
    _widget_manager.group_radiobuttons();
} // END@__build


// -----------------------------------------------------------------------------
