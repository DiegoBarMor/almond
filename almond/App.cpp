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
    while (const std::optional event = __window.pollEvent()) {
        if (_internal_manage_event(event)) continue;
        __root->handle_event(event);
    }
}

void nd::App::draw() {
    if (__root == nullptr) return;
    __root->draw(__window);
}

void nd::App::__init() {
    _prototypes = {};
    _table_id_widgets = {};
    nd::Widget* pt_generic   = new nd::Widget();
    nd::Widget* pt_container = new nd::Container();
    nd::Widget* pt_row       = new nd::RowLayout();
    nd::Widget* pt_col       = new nd::ColumnLayout();
    nd::Widget* pt_text      = new nd::Text();
    nd::Widget* pt_textinput = new nd::TextInput();
    nd::Widget* pt_button    = new nd::LabeledButton();
    nd::Widget* pt_checkbox  = new nd::CheckBox();
    nd::Widget* pt_radio     = new nd::RadioButton();
    _prototypes["SPACE"]        = pt_generic  ;
    _prototypes[""]             = pt_generic  ;
    _prototypes["CONTAINER"]    = pt_container;
    _prototypes["BOX"]          = pt_container;
    _prototypes["LAYOUTROW"]    = pt_row      ;
    _prototypes["ROW"]          = pt_row      ;
    _prototypes["LAYOUTCOL"]    = pt_col      ;
    _prototypes["COL"]          = pt_col      ;
    _prototypes["TEXT"]         = pt_text     ;
    _prototypes["TXT"]          = pt_text     ;
    _prototypes["TEXTINPUT"]    = pt_textinput;
    _prototypes["TIN"]          = pt_textinput;
    _prototypes["BUTTON"]       = pt_button   ;
    _prototypes["BTT"]          = pt_button   ;
    _prototypes["CHECKBOX"]     = pt_checkbox ;
    _prototypes["CBX"]          = pt_checkbox ;
    _prototypes["RADIOBUTTON"]  = pt_radio    ;
    _prototypes["RBN"]          = pt_radio    ;
}

void nd::App::__create(const std::string &filename) {
    if (filename != "") {
        __root = nd::NDGParser(_prototypes).parse(filename);
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
