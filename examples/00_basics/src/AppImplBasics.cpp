#include "AppImplBasics.hpp"

bool callback_key_press(AppImplBasics* gui) {
    nd::Event::KeyPressed key = gui->get_event_manager().get_key_pressed();

    std::cout << "Root key pressed: " << sf::Keyboard::getDescription(key.scancode).toAnsiString() << std::endl;
    if (key.code == sf::Keyboard::Key::Escape) {
        gui->get_window().close();
    }
    return true;
}

void AppImplBasics::_on_init() {
    ////// pre-creation operations, custom prototypes must be added here before parsing the GUI file
    _drawable_man.add_prototype("CUSTOM_WIDGET", new CustomWidget());
}

void AppImplBasics::_on_create() {
    nd::Widget* col0 = get_widget("col0");
    nd::LabeledButton* b0 = (nd::LabeledButton*)get_widget("b0");
    nd::LabeledButton* b1 = (nd::LabeledButton*)get_widget("b1");

    ////// arbitrary post-creation operations
    b1->set_spec("TEXT", "New text");
    b1->set_spec("BG_IDLE", "255,0,0,120");

    ////// linking callbacks with lambda expressions
    ////// note that the AppImplBasics instance has to be captured with [] to access its methods
    _event_man.add_on_key_pressed([this]() {
        return callback_key_press(this);
    });

    ////// can also link callbacks directly to widgets
    b0->link_on_event([this](nd::Event event) {
        if (event.none.type != nd::EventType::MOUSE_BUTTON_RELEASED) return false;

        std::cout << "Button 0 released" << std::endl;
        nd::Widget* custom = this->get_widget("custom");
        custom->set_spec("COLOR_0", "128,0,0");
        custom->build();
        ////// return values indicate whether the event is to be "consumed"
        ////// returning true will prevent the event from being propagated and processed by other widgets
        ////// returning false is useful when e.g. overlapping elements should both react to a mouse event
        return false;
    });

    ////// some widget types also provide their own specific callbacks, e.g. buttons have on_click
    b0->link_on_click([this](nd::Event event) {
        std::cout << "Button 0 clicked" << std::endl;
        nd::Widget* custom = this->get_widget("custom");
        custom->set_spec("COLOR_0", "128,128,128");
        custom->build();
        return false;
    });

    ////// any kind of widget can handle events, even containers
    col0->link_on_event([](nd::Event event) {
        if (event.none.type == nd::EventType::MOUSE_BUTTON_PRESSED)
            std::cout << "Column 0 clicked" << std::endl;
        else if (event.none.type == nd::EventType::MOUSE_BUTTON_RELEASED)
            std::cout << "Column 0 released" << std::endl;
        return false;
    });
}
