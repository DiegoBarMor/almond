#include "App.hpp"

void nd::App::setup(const std::string &filename, sf::Vector2f pos, sf::Vector2f size) {
    if (size == sf::Vector2f(0, 0)) {
        size = sf::Vector2f((float)__window.getSize().x, (float)__window.getSize().y);
    }

    __init();
    _on_init();

    __create(filename);
    _on_create();

    __build(pos, size);
    _on_build();
}

nd::Widget* nd::App::get_widget(std::string id) {
    nd::Widget* widget = nd::Widget::get_widget_by_id(id);
    if (widget == nullptr) {
        std::cerr << "WARNING: Widget '" << id << "' not found." << std::endl;
    }
    return widget;
}

void nd::App::manage_events() {
    if (__root == nullptr) return;
    sf::Event event;
    while (__window.pollEvent(event)) {
        if (_internal_manage_event(event)) continue;
        __root->handle_event(event);
    }
}

void nd::App::draw() {
    if (__root == nullptr) return;
    __root->draw(__window);
}

void nd::App::__init() {
    nd::Widget* pt_generic   = new nd::Widget();
    nd::Widget* pt_container = new nd::Container();
    nd::Widget* pt_row       = new nd::RowLayout();
    nd::Widget* pt_col       = new nd::ColumnLayout();
    nd::Widget* pt_text      = new nd::Text();
    nd::Widget* pt_textinput = new nd::TextInput();
    nd::Widget* pt_button    = new nd::LabeledButton();
    nd::Widget* pt_checkbox  = new nd::CheckBox();
    nd::Widget* pt_radio     = new nd::RadioButton();
    nd::Widget::add_prototype("SPACE",       pt_generic   );
    nd::Widget::add_prototype("",            pt_generic   );
    nd::Widget::add_prototype("CONTAINER",   pt_container );
    nd::Widget::add_prototype("BOX",         pt_container );
    nd::Widget::add_prototype("LAYOUTROW",   pt_row       );
    nd::Widget::add_prototype("ROW",         pt_row       );
    nd::Widget::add_prototype("LAYOUTCOL",   pt_col       );
    nd::Widget::add_prototype("COL",         pt_col       );
    nd::Widget::add_prototype("TEXT",        pt_text      );
    nd::Widget::add_prototype("TXT",         pt_text      );
    nd::Widget::add_prototype("TEXTINPUT",   pt_textinput );
    nd::Widget::add_prototype("TIN",         pt_textinput );
    nd::Widget::add_prototype("BUTTON",      pt_button    );
    nd::Widget::add_prototype("BTT",         pt_button    );
    nd::Widget::add_prototype("CHECKBOX",    pt_checkbox  );
    nd::Widget::add_prototype("CBX",         pt_checkbox  );
    nd::Widget::add_prototype("RADIOBUTTON", pt_radio     );
    nd::Widget::add_prototype("RBN",         pt_radio     );
}

void nd::App::__create(const std::string &filename) {
    if (filename != "") {
        __root = nd::NDGParser::parse(filename);
        if (__root == nullptr) {
            std::cerr << "Failed to parse NDG file: " << filename << std::endl;
            std::cout << "Creating empty Container as the root widget." << std::endl;
            __root = new nd::Container();
        }
    } else {
        std::cout << "No NDG file provided. Creating empty Container as the root widget." << std::endl;
        __root = new nd::Container();
    }
    __root->set_spec("ID", "root");
}

void nd::App::__build(sf::Vector2f pos, sf::Vector2f size) {
    __root->set_pos(pos);
    __root->set_size(size);
    __root->build();
}
