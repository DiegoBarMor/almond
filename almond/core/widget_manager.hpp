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


private:
    std::unordered_map<std::string, nd::Widget*> __prototypes;

};

////////////////////////////////////////////////////////////////////////////////
}
