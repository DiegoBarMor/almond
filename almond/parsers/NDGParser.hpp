#pragma once
#include <fstream>
#include "../core/widget_manager.hpp"
#include "../widgets/Widget.hpp"

namespace nd {
////////////////////////////////////////////////////////////////////////////////

class NDGParser {
public:
    enum class State {
        TYPE,      // parsing the "type" spec of the widget
        SPECS_KEY, // parsing the next spec key
        SPECS_VAL, // parsing the value for the current spec
        NEXT_GUI   // parsing brackets, deal with staying in the same GUI or moving to the next
    };
    NDGParser(nd::WidgetManager &widget_manager) : __widget_manager(widget_manager) {}
    Widget* parse(const std::string &filename);

private:
    void __parse_file(std::ifstream &file);
    void __parse_type(char ch);
    void __parse_specs_key(char ch);
    void __parse_specs_val(char ch);
    void __parse_next_gui(char ch);
    void __add_gui_widget();
    bool __ignore(char ch);

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

////////////////////////////////////////////////////////////////////////////////
}
