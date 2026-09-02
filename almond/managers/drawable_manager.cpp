#include "drawable_manager.hpp"

// -----------------------------------------------------------------------------
nd::DrawableManager::DrawableManager() { // FUNC@DrawableManager
    if (!__font.openFromMemory(nd::tff_crimson_roman, nd::size_crimson_roman)) {
        std::cerr << "Error loading font" << std::endl;
    }

    auto generic   = std::make_shared<Widget>();
    auto container = std::make_shared<Container>();
    auto row       = std::make_shared<LayoutRow>();
    auto col       = std::make_shared<LayoutColumn>();
    auto text      = std::make_shared<Text>(__font);
    auto textInput = std::make_shared<TextInput>(__font);
    auto button    = std::make_shared<LabeledButton>(__font);
    auto checkbox  = std::make_shared<CheckBox>();
    auto radio     = std::make_shared<RadioButton>();

    __prototypes = {};
    __prototypes["SPACE"]       = generic;
    __prototypes[""]            = generic;
    __prototypes["CONTAINER"]   = container;
    __prototypes["BOX"]         = container;
    __prototypes["LAYOUTROW"]   = row;
    __prototypes["ROW"]         = row;
    __prototypes["LAYOUTCOL"]   = col;
    __prototypes["COL"]         = col;
    __prototypes["TEXT"]        = text;
    __prototypes["TXT"]         = text;
    __prototypes["TEXTINPUT"]   = textInput;
    __prototypes["TIN"]         = textInput;
    __prototypes["BUTTON"]      = button;
    __prototypes["BTT"]         = button;
    __prototypes["CHECKBOX"]    = checkbox;
    __prototypes["CBX"]         = checkbox;
    __prototypes["RADIOBUTTON"] = radio;
    __prototypes["RBN"]         = radio;
} // END@DrawableManager


// -----------------------------------------------------------------------------
nd::Widget* nd::DrawableManager::create_widget(std::string type) { // FUNC@create_widget
    if (__prototypes.find(type) == __prototypes.end()) {
        std::cerr << "WARNING: Invalid GUI type: " << type << std::endl;
        return nullptr;
    }

    std::shared_ptr<nd::Widget> widget = __prototypes[type]->clone();
    __all_widgets.push_back(widget);

    if (type == "RBN" || type == "RADIOBUTTON") {
        __list_radiobuttons.push_back((nd::RadioButton*)widget.get());
    }
    return widget.get(); // [WIP]
} // END@create_widget


// -----------------------------------------------------------------------------
nd::Widget* nd::DrawableManager::get_widget_by_id(std::string id) { // FUNC@get_widget_by_id
    if (__id_widgets.find(id) == __id_widgets.end()) {
        std::cerr << "WARNING: Widget with id '" << id << "' not found." << std::endl;
        return nullptr;
    }
    return __id_widgets[id];
} // END@get_widget_by_id


// -----------------------------------------------------------------------------
void nd::DrawableManager::group_radiobuttons() { // FUNC@group_radiobuttons
    if (!__is_first_build) return;
    __is_first_build = false;

    if (__list_radiobuttons.size() == 0) return;
    __list_radiobuttons[0]->first_build(__list_radiobuttons);
} // END@group_radiobuttons


// -----------------------------------------------------------------------------
