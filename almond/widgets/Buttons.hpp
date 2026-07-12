#pragma once
#include "Texts.hpp"

namespace nd {
////////////////////////////////////////////////////////////////////////////////

class ButtonPrimitive : public Widget {
public:
    // m.0c (Lifecycle methods - SABHD)
    bool set_spec(std::string key, std::string raw_value) override;
    void build() override;

    // m.0d (Setters/Getters for the spec fields)
    void      set_enabled    (bool enabled);
    void      set_bg_idle    (sf::Color color) { __bg_idle = color;     }
    void      set_bg_hover   (sf::Color color) { __bg_hover = color;    }
    void      set_bg_pressed (sf::Color color) { __bg_pressed = color;  }
    void      set_bg_disabled(sf::Color color) { __bg_disabled = color; }
    bool      get_enabled    ();
    sf::Color get_bg_idle    ()                { return __bg_idle;      }
    sf::Color get_bg_hover   ()                { return __bg_hover;     }
    sf::Color get_bg_pressed ()                { return __bg_pressed;   }
    sf::Color get_bg_disabled()                { return __bg_disabled;  }

protected:
    ButtonPrimitive() : Widget() { _bg_color = __bg_idle; }

    // m.1b (Callback wrappers)
    bool _internal_on_mouse_click  (sf::Event event) override;
    bool _internal_on_mouse_release(sf::Event event) override;
    bool _internal_on_mouse_move   (sf::Event event) override;

    // d.1d (Other fields)
    enum class State {
        IDLE,    // button isn't pressed and mouse isn't over it
        HOVER,   // button isn't pressed and mouse is over it
        PRESSED, // button is pressed. Mouse could be over it or not
        DISABLED // button is disabled and can't be interacted with
    } _state = State::IDLE;

private:
    // m.2a (Internal functionalities)
    void __set_state(State state);

    // d.2b (Spec fields)
    sf::Color __bg_idle     = sf::Color(0x4A4A4AFF);
    sf::Color __bg_hover    = sf::Color(0x0066AFFF);
    sf::Color __bg_pressed  = sf::Color(0x5387ADFF);
    sf::Color __bg_disabled = sf::Color(0x222222FF);
};

////////////////////////////////////////////////////////////////////////////////

class LabeledButton : public ButtonPrimitive {
public:
    // m.0a (Construction methods)
    LabeledButton() : ButtonPrimitive() {}
    LabeledButton *clone() override { return new LabeledButton(); }

    // m.0c (Lifecycle methods - SABHD)
    bool set_spec(std::string key, std::string raw_value) override;
    void build() override;
    void draw(sf::RenderWindow& window) override;

    // m.0e (Setters/Getters for other internal fields)
    nd::Text& get_text_widget() { return __text_widget; }

private:
    // d.2c (Other fields)
    nd::Text __text_widget = nd::Text();
};

////////////////////////////////////////////////////////////////////////////////

class ToggleableButton : public ButtonPrimitive {
public:
    // m.0c (Lifecycle methods - SABHD)
    bool set_spec(std::string key, std::string raw_value) override;
    void build() override;
    bool handle_event(sf::Event event) override;
    void draw(sf::RenderWindow& window) override;

    // m.0d (Setters/Getters for the spec fields)
    void      set_checked          (bool checked)    { _checked = checked;             }
    void      set_color_mark       (sf::Color color) { _color_mark = color;            }
    void      set_outline_thickness(float thickness) { _outline_thickness = thickness; }
    bool      get_checked          ()                { return _checked;                }
    sf::Color get_color_mark       ()                { return _color_mark;             }
    float     get_outline_thickness()                { return _outline_thickness;      }

    // m.0f (Linkers for the callbacks)
    virtual void link_on_toggle(CALLBACK_VOID callback) { _on_toggle = callback; }

protected:
    ToggleableButton() : ButtonPrimitive() {}

    // m.1b (Callback wrappers)
    virtual void _internal_on_toggle() {};

    // d.1b (Spec fields)
    bool _checked = false;
    sf::Color _color_mark = sf::Color(0,0,200,200);
    float _outline_thickness = 0.2f; // ratio (0.0f-1.0f) [WIP]

    // d.1c (Client callbacks)
    CALLBACK_VOID _on_toggle;

    // d.1d (Other fields)
    sf::Color _color_overlay = sf::Color(255, 255, 255, 128);
    sf::RectangleShape _shape_overlay = sf::RectangleShape();
};

////////////////////////////////////////////////////////////////////////////////

class CheckBox : public ToggleableButton {
public:
    // m.0a (Construction methods)
    CheckBox() : ToggleableButton() {}
    CheckBox* clone() override { return new CheckBox(); }

    // m.0c (Lifecycle methods - SABHD)
    void build() override;
    void draw(sf::RenderWindow& window) override;

protected:
    // m.1b (Callback wrappers)
    void _internal_on_toggle() override;

private:
    // d.2c (Other fields)
    sf::VertexArray __check_mark = sf::VertexArray(sf::PrimitiveType::TriangleStrip, 6);
};


////////////////////////////////////////////////////////////////////////////////

class RadioButton : public ToggleableButton {
public:
    // m.0a (Construction methods)
    RadioButton() : ToggleableButton() { }
    RadioButton* clone() override;

    // m.0c (Lifecycle methods - SABHD)
    bool set_spec(std::string key, std::string raw_value) override;
    void build() override;
    void draw(sf::RenderWindow& window) override;

    // m.0d (Setters/Getters for the spec fields)
    std::string get_group_id() { return __group_id; }

protected:
    // m.1b (Callback wrappers)
    void _internal_on_toggle() override;

private:
    struct RadioButtonGroup {
        int selected_idx = -1;
        std::vector<RadioButton*> buttons = {};
    };

    // m.2a (Internal functionalities)
    void __first_build();

    // d.2a (Static fields)
    static bool __is_first_build;
    static std::vector<RadioButton*> __list_radiobuttons;
    static std::unordered_map<std::string, RadioButtonGroup*> __table_groups;

    // d.2b (Spec fields)
    std::string __group_id = "";

    // d.2c (Other fields)
    RadioButtonGroup* __group = nullptr;
    int __idx_in_group = -1;

    sf::CircleShape __check_mark = sf::CircleShape();
    float __check_mark_ratio = 0.5f; // ratio (0.0f-1.0f) of the marker's size to the button's size
};

////////////////////////////////////////////////////////////////////////////////
}
