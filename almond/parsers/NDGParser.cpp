#include "NDGParser.hpp"

nd::Widget* nd::NDGParser::parse(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return nullptr;
    }
    __parse_file(file);
    file.close();
    return __root;
}

void nd::NDGParser::__parse_file(std::ifstream &file) {
    char ch;
    while (file.get(ch)) {
        if (ch == '\n' || ch == '\r') {
            __reading_comment = false;
            continue;
        }
        switch (__state) {
        case State::TYPE:
            __parse_type(ch); break;
        case State::SPECS_KEY:
            __parse_specs_key(ch); break;
        case State::SPECS_VAL:
            __parse_specs_val(ch); break;
        case State::NEXT_GUI:
            __parse_next_gui(ch); break;
        }
    }
}

void nd::NDGParser::__parse_type(char ch) {
    if (__ignore(ch)) return;
    if (ch != '(' && ch != '{') {
        __buffer += toupper(ch);
        return;
    }
    __parse_next_gui(ch);
    __buffer = "";
}

void nd::NDGParser::__parse_specs_key(char ch) {
    if (__ignore(ch)) return;
    if (ch == ')') {
        __state = State::NEXT_GUI;
        return;
    }
    if (ch != '=') {
        __buffer += toupper(ch);
        return;
    }
    __specs_key = __buffer;
    __state = State::SPECS_VAL;
    __buffer = "";
}

void nd::NDGParser::__parse_specs_val(char ch) {
    if (ch == '"') {
        __quote_open = !__quote_open;
        return;
    }
    if (__quote_open) {
        __buffer += ch;
        return;
    }
    if (__ignore(ch)) return;
    if (ch != ';' && ch != ')') {
        __buffer += toupper(ch);
        return;
    }
    if (__current != nullptr) {
        if (!__current->set_spec(__specs_key, __buffer)) {
            std::cerr << "Failed to set spec: " <<
            __specs_key << " = " << __buffer << std::endl;
        }
    }
    __state = ch == ';' ? State::SPECS_KEY : State::NEXT_GUI;
    __buffer = "";
}

void nd::NDGParser::__parse_next_gui(char ch) {
    if (__ignore(ch)) return;
    if (ch == '(') {
        __add_gui_widget();
        __state = State::SPECS_KEY;
        return;
    }
    if (ch == '{') {
        if (__buffer != "") { __add_gui_widget(); } // skipping "type" isn't allowed if no "()" is specified
        __parent = __current;
        __state = State::TYPE;
        return;
    }
    if (ch == '}') {
        if (__parent != nullptr) { __parent = __parent->get_parent(); }
        return;
    }
    __buffer += toupper(ch);
    __state = State::TYPE;
}

void nd::NDGParser::__add_gui_widget() {
    __current = __widget_manager.create_widget(__buffer);
    if (__current == nullptr) {
        std::cerr << "Failed to create widget: " << __buffer << std::endl;
        return;
    }
    if (__root == nullptr) {
        __root = __current;
        return;
    }
    if (__parent == nullptr) { __parent = __root; }
    __parent->add_child(__current);
}

bool nd::NDGParser::__ignore(char ch) {
    if (ch == '#') { __reading_comment = true; }
    return __reading_comment || std::isspace(ch);
}
