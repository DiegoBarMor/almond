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
std::shared_ptr<nd::Widget> nd::DrawableManager::create_widget(std::string type) { // FUNC@create_widget
    if (__prototypes.find(type) == __prototypes.end()) {
        std::cerr << "WARNING: Invalid GUI type: " << type << std::endl;
        return nullptr;
    }

    std::shared_ptr<nd::Widget> widget = __prototypes[type]->clone();
    __all_widgets.push_back(widget);

    return widget; // [WIP]
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

    std::unordered_map<std::string, nd::RadioButton::RadioButtonGroup*> table_groups = {};
    for (std::shared_ptr<nd::Widget> widget : __all_widgets) {
        nd::RadioButton* rb = dynamic_cast<nd::RadioButton*>(widget.get()); // [WIP]
        if (rb == nullptr) continue;

        const std::string& group_id = rb->get_group_id();

        nd::RadioButton::RadioButtonGroup* group = table_groups[group_id];
        if (group == nullptr) {
            group = new nd::RadioButton::RadioButtonGroup();
            table_groups[group_id] = group;
        }
        rb->add_to_group(group);
    }

    for (auto& [group_id, group] : table_groups) {
        if (group->selected_idx == -1) group->selected_idx = 0;
        auto selected_button = group->buttons[group->selected_idx];
        selected_button->set_checked(true);
    }
} // END@group_radiobuttons


// -----------------------------------------------------------------------------
