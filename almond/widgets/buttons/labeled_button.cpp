#include "labeled_button.hpp"

// -----------------------------------------------------------------------------
bool nd::LabeledButton::set_spec(std::string key, std::string raw_value) { // FUNC@set_spec
    if (nd::ButtonPrimitive::set_spec(key, raw_value))
        return true;
    return __text_widget.set_spec(key, raw_value);
} // END@set_spec


// -----------------------------------------------------------------------------
void nd::LabeledButton::build() { // FUNC@build
    nd::ButtonPrimitive::build();
    __text_widget.set_pos(get_pos());
    __text_widget.set_size(get_size());
    __text_widget.build();
} // END@build


// -----------------------------------------------------------------------------
void nd::LabeledButton::draw(sf::RenderWindow& window) { // FUNC@draw
    nd::ButtonPrimitive::draw(window);
    __text_widget.draw(window);
} // END@draw


// -----------------------------------------------------------------------------
