#pragma once
#include "../widgets/Widget.hpp"
#include "../widgets/Containers.hpp"
#include "../widgets/Buttons.hpp"

namespace nd {
////////////////////////////////////////////////////////////////////////////////

class WidgetManager {
public:
    WidgetManager();

    void add_prototype(std::string type, nd::Widget* prototype) {
        __prototypes[type] = prototype;
    }
    nd::Widget* create_widget(std::string type);

    void set_id(nd::Widget* widget, std::string id);
    Widget* get_widget_by_id(std::string id);

    void group_radiobuttons();

private:
    std::unordered_map<std::string, nd::Widget*> __prototypes;
    std::unordered_map<std::string, nd::Widget*> __id_widgets;

    bool __is_first_build = true;
    std::vector<nd::RadioButton*> __list_radiobuttons = {};
};

////////////////////////////////////////////////////////////////////////////////
}
