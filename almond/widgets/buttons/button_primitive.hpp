#pragma once
#include "../widget.hpp"

namespace nd {
class ButtonPrimitive : public Widget {
public:
    bool set_spec(std::string key, std::string raw_value) override; // HEAD@set_spec
    void build() override; // HEAD@build
    bool handle_event(nd::Event event) override; // HEAD@handle_event

    void      set_enabled    (bool enabled); // HEAD@set_enabled
    void      set_bg_idle    (sf::Color color) { __bg_idle = color;     }
    void      set_bg_hover   (sf::Color color) { __bg_hover = color;    }
    void      set_bg_pressed (sf::Color color) { __bg_pressed = color;  }
    void      set_bg_disabled(sf::Color color) { __bg_disabled = color; }
    bool      get_enabled    (); // HEAD@get_enabled
    sf::Color get_bg_idle    () { return __bg_idle;     }
    sf::Color get_bg_hover   () { return __bg_hover;    }
    sf::Color get_bg_pressed () { return __bg_pressed;  }
    sf::Color get_bg_disabled() { return __bg_disabled; }

    void link_on_click(CALLBACK_EVENT callback) { _on_click = callback; }

protected:
    ButtonPrimitive() : Widget() { _bg_color = __bg_idle; }

    virtual bool _on_mouse_button_pressed(nd::Event event); // HEAD@_on_mouse_button_pressed
    virtual bool _on_mouse_button_released(nd::Event event); // HEAD@_on_mouse_button_released
    virtual bool _on_mouse_moved(nd::Event event); // HEAD@_on_mouse_moved

    enum class State {
        IDLE,    // button isn't pressed and mouse isn't over it
        HOVER,   // button isn't pressed and mouse is over it
        PRESSED, // button is pressed. Mouse could be over it or not
        DISABLED // button is disabled and can't be interacted with
    } _state = State::IDLE;

    CALLBACK_EVENT _on_click;

private:
    void __set_state(State state); // HEAD@__set_state

    sf::Color __bg_idle     = sf::Color(0x4A4A4AFF);
    sf::Color __bg_hover    = sf::Color(0x0066AFFF);
    sf::Color __bg_pressed  = sf::Color(0x5387ADFF);
    sf::Color __bg_disabled = sf::Color(0x222222FF);
};
}
