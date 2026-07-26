#include "AppImplBasics.hpp"

bool callback_key_press(AppImplBasics* gui, const std::optional<sf::Event> event) {
    const auto* keyPress = event->getIf<sf::Event::KeyPressed>();
    std::cout << "Root key pressed: " << sf::Keyboard::getDescription(keyPress->scancode).toAnsiString() << std::endl;
    if (keyPress && keyPress->code == sf::Keyboard::Key::Escape) {
        gui->get_window().close();
    }
    return true;
}

void AppImplBasics::_on_init() {
    // pre-creation operations, custom prototypes must be added here before parsing the GUI file
    _widget_manager.add_prototype("CUSTOM_WIDGET", new CustomWidget());
}

void AppImplBasics::_on_create() {
    nd::Widget* root = get_widget("root");
    nd::Widget* col0 = get_widget("col0");
    nd::Widget* b0   = get_widget("b0");
    nd::Widget* b1   = get_widget("b1");

    // arbitrary post-creation operations
    b1->set_spec("TEXT", "New text");
    b1->set_spec("BG_IDLE", "255,0,0,120");

    // linking callbacks with lambda expressions
    // note that the AppImplBasics instance has to be captured with [] to access its methods
    root->link_on_key_pressed([this](const std::optional<sf::Event> event) {
        return callback_key_press(this, event);
    });

    // can also link callbacks directly to widgets, to avoid wasting time searching for them multiple times
    col0->link_on_mouse_button_pressed([](const std::optional<sf::Event> event) {
        // any kind of widget can handle events, even containers
        std::cout << "Column 0 clicked" << std::endl;
        return true;
    });
    col0->link_on_mouse_button_released([](const std::optional<sf::Event> event) {
        std::cout << "Column 0 released" << std::endl;
        return true;
    });
    b0->link_on_mouse_button_pressed([this](const std::optional<sf::Event> event) {
        std::cout << "Button 0 clicked" << std::endl;
        nd::Widget* custom = this->get_widget("custom");
        custom->set_spec("COLOR_0", "128,128,128");
        custom->build();
        // return true to stop the event propagation
        return true;
    });
    b0->link_on_mouse_button_released([this](const std::optional<sf::Event> event) {
        std::cout << "Button 0 released" << std::endl;
        nd::Widget* custom = this->get_widget("custom");
        custom->set_spec("COLOR_0", "128,0,0");
        custom->build();
        // return false to allow the parent container to also handle the same event
        // note that this will also lead to potentially unnecessary event handling by this widget's siblings
        return false;
    });
}
