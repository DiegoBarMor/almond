#include "parser_ndg.hpp"

// -----------------------------------------------------------------------------
nd::Widget* nd::ParserNDG::parse(const std::string& filename) { // FUNC@parse
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return nullptr;
    }
    __parse_file(file);
    file.close();
    return __root;
} // END@parse


// -----------------------------------------------------------------------------
void nd::ParserNDG::__parse_file(std::ifstream& file) { // FUNC@__parse_file
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
} // END@__parse_file


// -----------------------------------------------------------------------------
void nd::ParserNDG::__parse_type(char ch) { // FUNC@__parse_type
    if (__ignore(ch)) return;
    if (ch != '(' && ch != '{') {
        __buffer += toupper(ch);
        return;
    }
    __parse_next_gui(ch);
    __buffer = "";
} // END@__parse_type


// -----------------------------------------------------------------------------
void nd::ParserNDG::__parse_specs_key(char ch) { // FUNC@__parse_specs_key
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
} // END@__parse_specs_key


// -----------------------------------------------------------------------------
void nd::ParserNDG::__parse_specs_val(char ch) { // FUNC@__parse_specs_val
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
        if (__specs_key == "ID" || __specs_key == "IDENTIFIER") {
            __manager_drawables.set_id(__current, __buffer);
        }
        else if (!__current->set_spec(__specs_key, __buffer)) {
            std::cerr << "Failed to set spec: " <<
            __specs_key << " = " << __buffer << std::endl;
        }
    }
    __state = ch == ';' ? State::SPECS_KEY : State::NEXT_GUI;
    __buffer = "";
} // END@__parse_specs_val


// -----------------------------------------------------------------------------
void nd::ParserNDG::__parse_next_gui(char ch) { // FUNC@__parse_next_gui
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
} // END@__parse_next_gui


// -----------------------------------------------------------------------------
void nd::ParserNDG::__add_gui_widget() { // FUNC@__add_gui_widget
    __current = __manager_drawables.create_widget(__buffer);
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
} // END@__add_gui_widget


// -----------------------------------------------------------------------------
bool nd::ParserNDG::__ignore(char ch) { // FUNC@__ignore
    if (ch == '#') { __reading_comment = true; }
    return __reading_comment || std::isspace(ch);
} // END@__ignore


// -----------------------------------------------------------------------------
