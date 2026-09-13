#pragma once
#include "../core/globals.hpp"
#include "../parsers/parser_strings.hpp"
#include "../events/event.hpp"

namespace nd {
class Widget : public std::enable_shared_from_this<Widget> {
public:
    virtual ~Widget() = default;
    Widget() {};
    virtual std::unique_ptr<Widget> clone() const {
        return std::make_unique<Widget>();
    }

    virtual bool set_spec(std::string key, std::string raw_value); // HEAD@set_spec
    virtual void add_child(std::shared_ptr<Widget> child); // HEAD@add_child
    virtual void build(); // HEAD@build
    virtual bool handle_event(const nd::Event& event); // HEAD@handle_event
    virtual void draw(sf::RenderWindow& window); // HEAD@draw

    void set_weight  (float weight   ) { __weight = weight; }
    void set_bg_color(const sf::Color& color); // HEAD@set_bg_color

    float            get_weight  () const { return __weight;  }
    const sf::Color& get_bg_color() const { return _bg_color; }

    virtual void set_pos (sf::Vector2f pos ) { _pos = pos;   }
    virtual void set_size(sf::Vector2f size) { _size = size; }
    sf::Vector2f get_pos () { return _pos;  }
    sf::Vector2f get_size() { return _size; }

    void set_parent(std::weak_ptr<Widget> parent) {
        __parent = std::move(parent);
    }
    std::shared_ptr<Widget> get_parent() const {
        return __parent.lock();
    }

    bool contains_point(sf::Vector2i point); // HEAD@contains_point
    void force_widget_square(); // HEAD@force_widget_square

    virtual void link_on_event(CALLBACK_EVENT callback) { _on_event = callback; }

protected:
    void _init_shape(); // HEAD@_init_shape

    sf::Vector2f _pos  = {0, 0};
    sf::Vector2f _size = {0, 0};
    sf::RectangleShape _shape = sf::RectangleShape();
    sf::Color _bg_color = sf::Color::Transparent;

    CALLBACK_EVENT _on_event;

private:
    float __weight = 1.f;

    std::weak_ptr<Widget> __parent = std::weak_ptr<Widget>();
};
}
