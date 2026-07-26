#pragma once
#include <fstream>
#include "../core/widget_manager.hpp"
#include "../widgets/Widget.hpp"

namespace nd {
class ParserNDG {
public:
    enum class State {
        TYPE,      // parsing the "type" spec of the widget
        SPECS_KEY, // parsing the next spec key
        SPECS_VAL, // parsing the value for the current spec
        NEXT_GUI   // parsing brackets, deal with staying in the same GUI or moving to the next
    };
    ParserNDG(nd::WidgetManager &widget_manager) : __widget_manager(widget_manager) {}
    Widget* parse(const std::string &filename); // HEAD@parse

private:
    void __parse_file(std::ifstream &file); // HEAD@__parse_file
    void __parse_type(char ch); // HEAD@__parse_type
    void __parse_specs_key(char ch); // HEAD@__parse_specs_key
    void __parse_specs_val(char ch); // HEAD@__parse_specs_val
    void __parse_next_gui(char ch); // HEAD@__parse_next_gui
    void __add_gui_widget(); // HEAD@__add_gui_widget
    bool __ignore(char ch); // HEAD@__ignore

    bool __reading_comment = false;
    bool __quote_open = false;
    std::string __buffer = "";
    std::string __specs_key = "";

    nd::WidgetManager& __widget_manager;

    State __state = State::TYPE;
    Widget* __root = nullptr;
    Widget* __parent = nullptr;
    Widget* __current = nullptr;
};
}
