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
    return _drawable_man.get_widget_by_id(id);
} // END@get_widget


// -----------------------------------------------------------------------------
void nd::App::manage_events() { // FUNC@manage_events
    while (const std::optional sf_event = __window.pollEvent()) {
        nd::Event nd_event = __init_event(sf_event);
        _event_man.handle_event(nd_event);

        for (std::shared_ptr<nd::Widget> widget : _drawable_man.get_all_widgets()) {
            bool consumed = widget->handle_event(nd_event);
            if (consumed) break;
        }
    }
} // END@manage_events


// -----------------------------------------------------------------------------
void nd::App::draw() { // FUNC@draw
    if (__root_widget == nullptr) return;
    __root_widget->draw(__window);
} // END@draw


// -----------------------------------------------------------------------------
void nd::App::__create(const std::string& filename) { // FUNC@__create
    if (filename != "") {
        __root_widget = nd::ParserNDG(_drawable_man).parse(filename);
        if (__root_widget == nullptr) {
            std::cerr << "Failed to parse NDG file: " << filename << std::endl;
            std::cout << "Creating empty Container as the root widget." << std::endl;
            __root_widget.reset(_drawable_man.create_widget("CONTAINER"));
        }
    } else {
        std::cout << "No NDG file provided. Creating empty Container as the root widget." << std::endl;
        __root_widget.reset(_drawable_man.create_widget("CONTAINER"));
    }
    _drawable_man.set_id(__root_widget.get(), "root");
} // END@__create


// -----------------------------------------------------------------------------
void nd::App::__build(sf::Vector2f pos, sf::Vector2f size) { // FUNC@__build
    if (__root_widget == nullptr) return;
    __root_widget->set_pos(pos);
    __root_widget->set_size(size);
    __root_widget->build();
    _drawable_man.group_radiobuttons();
} // END@__build


// -----------------------------------------------------------------------------
