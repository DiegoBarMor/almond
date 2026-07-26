#pragma once
#include "../widgets/Widget.hpp"
#include "../widgets/Containers.hpp"
#include "../widgets/Buttons.hpp"

namespace nd {
class WidgetManager {
public:
    WidgetManager(); // HEAD@WidgetManager

    void add_prototype(std::string type, nd::Widget* prototype) {
        __prototypes[type] = prototype;
    }
    nd::Widget* create_widget(std::string type); // HEAD@create_widget

    void set_id(nd::Widget* widget, std::string id) { __id_widgets[id] = widget; }
    Widget* get_widget_by_id(std::string id); // HEAD@get_widget_by_id

    void group_radiobuttons(); // HEAD@group_radiobuttons

private:
    std::unordered_map<std::string, nd::Widget*> __prototypes;
    std::unordered_map<std::string, nd::Widget*> __id_widgets;

    sf::Font __font;
    bool __is_first_build = true;
    std::vector<nd::RadioButton*> __list_radiobuttons = {};
};
}
