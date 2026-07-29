#pragma once
#include "../widgets/widget.hpp"
#include "../widgets/buttons/button_primitive.hpp"
#include "../widgets/buttons/check_box.hpp"
#include "../widgets/buttons/labeled_button.hpp"
#include "../widgets/buttons/radio_button.hpp"
#include "../widgets/buttons/toggleable_button.hpp"
#include "../widgets/containers/container.hpp"
#include "../widgets/containers/layout_column.hpp"
#include "../widgets/containers/layout_row.hpp"
#include "../widgets/texts/text.hpp"
#include "../widgets/texts/text_input.hpp"

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

    sf::Font get_font() { return __font; }
    void set_font(sf::Font font) { __font = font; }

private:
    std::unordered_map<std::string, nd::Widget*> __prototypes;
    std::unordered_map<std::string, nd::Widget*> __id_widgets;

    sf::Font __font;
    bool __is_first_build = true;
    std::vector<nd::RadioButton*> __list_radiobuttons = {};
};
}
