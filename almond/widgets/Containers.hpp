#pragma once
#include "Widget.hpp"

namespace nd {

////////////////////////////////////////////////////////////////////////////////

class Container : public Widget {
public:
    // m.0a (Construction methods)
    Container() : Widget() {}
    Container* clone() override { return new Container(); }

    // m.0c (Lifecycle methods - SABHD)
    bool set_spec(std::string key, std::string raw_value) override;
    void add_child(Widget*) override;
    void build() override;
    bool handle_event(const std::optional<sf::Event> event) override;
    void draw(sf::RenderWindow& window) override;

    // m.0d (Setters/Getters for the spec fields)
    void  set_padding(float padding) { __padding = padding; }
    void  set_spacing(float spacing) { __spacing = spacing; }
    float get_padding()              { return __padding;    }
    float get_spacing()              { return __spacing;    }

protected:
    // m.1a (Internal functionalities)
    float _calc_offset_pos (int child_index);
    float _calc_offset_size(int child_index);

    // d.1d (Other fields)
    std::vector<Widget*> _children;
    int _num_children = 0;

private:
    // d.2b (Spec fields)
    float __padding = 0; // padding between the children and the container
    float __spacing = 0; // spacing between the children widgets
};

////////////////////////////////////////////////////////////////////////////////

class RowLayout : public Container {
public:
    // m.0a (Construction methods)
    RowLayout() : Container() {}
    RowLayout* clone() override { return new RowLayout(); }

    // m.0c (Lifecycle methods - SABHD)
    void build() override;
};

////////////////////////////////////////////////////////////////////////////////

class ColumnLayout : public Container {
public:
    // m.0a (Construction methods)
    ColumnLayout() : Container() {}
    ColumnLayout* clone() override { return new ColumnLayout(); }

    // m.0c (Lifecycle methods - SABHD)
    void build() override;
};

////////////////////////////////////////////////////////////////////////////////
}
