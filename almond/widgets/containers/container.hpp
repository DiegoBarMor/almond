#pragma once
#include "../widget.hpp"

namespace nd {
class Container : public Widget {
public:
    Container() : Widget() {}
    Container* clone() override { return new Container(); }

    bool set_spec(std::string key, std::string raw_value) override; // HEAD@set_spec
    void add_child(Widget* child) override; // HEAD@add_child
    void build() override; // HEAD@build
    bool handle_event(const std::optional<sf::Event> event) override; // HEAD@handle_event
    void draw(sf::RenderWindow& window) override; // HEAD@draw

    void  set_padding(float padding) { __padding = padding; }
    void  set_spacing(float spacing) { __spacing = spacing; }
    float get_padding() { return __padding; }
    float get_spacing() { return __spacing; }

protected:
    float _calc_offset_pos (int child_index); // HEAD@_calc_offset_pos
    float _calc_offset_size(int child_index); // HEAD@_calc_offset_size

    std::vector<Widget*> _children;
    int _num_children = 0;

private:
    float __padding = 0; // padding between the children and the container
    float __spacing = 0; // spacing between the children widgets
};
}
