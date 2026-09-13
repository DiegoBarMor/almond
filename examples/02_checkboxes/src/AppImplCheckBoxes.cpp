#include "AppImplCheckBoxes.hpp"

bool callback_key_press(AppImplCheckBoxes* gui) {
    nd::Event::KeyPressed key = gui->get_event_manager().get_key_pressed();

    std::cout << "Root key pressed: " << sf::Keyboard::getDescription(key.scancode).toAnsiString() << std::endl;
    if (key.code == sf::Keyboard::Key::Escape) {
        gui->get_window().close();
    }
    return true;
}

bool callback_on_toggle(std::shared_ptr<nd::CheckBox> cb) {
    std::string t;
    sf::Color color_0, color_1;
    if (cb->get_checked()) {
        t = "on";
        color_0 = sf::Color(0, 128, 0);
        color_1 = sf::Color(0, 200, 0);
    } else {
        t = "off";
        color_0 = sf::Color(128, 0, 0);
        color_1 = sf::Color(200, 0, 0);
    }
    std::cout << "CheckBox  " << cb << " toggled " << t << std::endl;
    cb->set_bg_idle(color_0);
    cb->set_bg_hover(color_1);
    return true;
}

void AppImplCheckBoxes::_on_init() {
    ////// pre-creation operations, custom prototypes must be added here before parsing the GUI file
}

void AppImplCheckBoxes::_on_create() {
    std::shared_ptr<nd::CheckBox> c0 = std::static_pointer_cast<nd::CheckBox>(get_widget("c0").lock());
    std::shared_ptr<nd::CheckBox> c1 = std::static_pointer_cast<nd::CheckBox>(get_widget("c1").lock());
    std::shared_ptr<nd::CheckBox> c2 = std::static_pointer_cast<nd::CheckBox>(get_widget("c2").lock());
    std::shared_ptr<nd::CheckBox> c3 = std::static_pointer_cast<nd::CheckBox>(get_widget("c3").lock());
    if (!c0 || !c1 || !c2 || !c3) {
        std::cerr << "Error: Failed to retrieve widgets by ID." << std::endl;
        return;
    }

    ////////linking callbacks with lambda expressions
    ////// note that the AppImplCheckBoxes instance has to be captured with [] to access its methods
    _event_man.add_on_key_pressed([this](const nd::Event& event) {
        return callback_key_press(this);
    });

    c0->link_on_toggle( [c0](const nd::Event& event){ return callback_on_toggle(c0); } );
    c1->link_on_toggle( [c1](const nd::Event& event){ return callback_on_toggle(c1); } );
    c2->link_on_toggle( [c2](const nd::Event& event){ return callback_on_toggle(c2); } );
    c3->link_on_toggle( [c3](const nd::Event& event){ return callback_on_toggle(c3); } );
}

void AppImplCheckBoxes::_on_build() {
    ////// post-building operations
}
