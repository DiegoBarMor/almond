#include "manager_drawables.hpp"

// -----------------------------------------------------------------------------
nd::ManagerDrawables::ManagerDrawables() { // FUNC@ManagerDrawables
    if (!__font.openFromMemory(nd::tff_crimson_roman, nd::size_crimson_roman)) {
        std::cerr << "Error loading font" << std::endl;
    }

    __prototypes = {};
    nd::Widget* pt_generic   = new nd::Widget();
    nd::Widget* pt_container = new nd::Container();
    nd::Widget* pt_row       = new nd::LayoutRow();
    nd::Widget* pt_col       = new nd::LayoutColumn();
    nd::Widget* pt_text      = new nd::Text(__font);
    nd::Widget* pt_textinput = new nd::TextInput(__font);
    nd::Widget* pt_button    = new nd::LabeledButton(__font);
    nd::Widget* pt_checkbox  = new nd::CheckBox();
    nd::Widget* pt_radio     = new nd::RadioButton();
    __prototypes["SPACE"]       = pt_generic  ;
    __prototypes[""]            = pt_generic  ;
    __prototypes["CONTAINER"]   = pt_container;
    __prototypes["BOX"]         = pt_container;
    __prototypes["LAYOUTROW"]   = pt_row      ;
    __prototypes["ROW"]         = pt_row      ;
    __prototypes["LAYOUTCOL"]   = pt_col      ;
    __prototypes["COL"]         = pt_col      ;
    __prototypes["TEXT"]        = pt_text     ;
    __prototypes["TXT"]         = pt_text     ;
    __prototypes["TEXTINPUT"]   = pt_textinput;
    __prototypes["TIN"]         = pt_textinput;
    __prototypes["BUTTON"]      = pt_button   ;
    __prototypes["BTT"]         = pt_button   ;
    __prototypes["CHECKBOX"]    = pt_checkbox ;
    __prototypes["CBX"]         = pt_checkbox ;
    __prototypes["RADIOBUTTON"] = pt_radio    ;
    __prototypes["RBN"]         = pt_radio    ;
} // END@ManagerDrawables


// -----------------------------------------------------------------------------
nd::Widget* nd::ManagerDrawables::create_widget(std::string type) { // FUNC@create_widget
    if (__prototypes.find(type) == __prototypes.end()) {
        std::cerr << "WARNING: Invalid GUI type: " << type << std::endl;
        return nullptr;
    }

    nd::Widget* widget = __prototypes[type]->clone();
    if (type == "RBN" || type == "RADIOBUTTON") {
        __list_radiobuttons.push_back((nd::RadioButton*)widget);
    }
    return widget;
} // END@create_widget


// -----------------------------------------------------------------------------
nd::Widget* nd::ManagerDrawables::get_widget_by_id(std::string id) { // FUNC@get_widget_by_id
    if (__id_widgets.find(id) == __id_widgets.end()) {
        std::cerr << "WARNING: Widget with id '" << id << "' not found." << std::endl;
        return nullptr;
    }
    return __id_widgets[id];
} // END@get_widget_by_id


// -----------------------------------------------------------------------------
void nd::ManagerDrawables::group_radiobuttons() { // FUNC@group_radiobuttons
    if (!__is_first_build) return;
    __is_first_build = false;

    if (__list_radiobuttons.size() == 0) return;
    __list_radiobuttons[0]->first_build(__list_radiobuttons);
} // END@group_radiobuttons


// -----------------------------------------------------------------------------
