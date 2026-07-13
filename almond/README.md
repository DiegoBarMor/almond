# Code conventions
The classes deriving from `nd::Widget` should follow these conventions, specially the order in which methods and fields are defined and declared.

1) Public interface (0)
    1) Methods (m.0)
        1) Construction methods (m.0a)
        2) Static methods (m.0b)
        3) Lifecycle methods - SABHD (m.0c)
        4) Setters/Getters for spec fields (m.0d)
        5) Setters/Getters for other internal fields (m.0e)
        6) Linkers for the callbacks (m.0f)
        7) Other functionalities (m.0g)
2) Protected (1)
    1) Methods (m.1)
        1) Internal functionalities (m.1a)
        2) Callback wrappers (m.1b)
    2) Data (d.1)
        1) Static fields (d.1a)
        2) Spec fields (d.1b)
        4) Client callbacks (d.1c)
        3) Other fields (d.1d)
3) Private (2)
    1) Methods (m.2)
        1) Internal functionalities (m.2a)
    2) Data (d.2)
        1) Static fields (d.2a)
        2) Spec fields (d.2b)
        3) Other fields (d.2c)
```
class NewClass : public ParentClass {
public:
    // m.0a (Construction methods)
    NewClass : ParentClass {}
    NewClass* clone() override { return new NewClass(); }

    // m.0b (Static methods)
    static void some_static_method(std::string str, nd::Widget* widget);

    // m.0c (Lifecycle methods - SABHD)
    bool set_spec(std::string key, std::string raw_value) override;
    void add_child(Widget*) override;
    void build() override;
    bool handle_event(const std::optional<sf::Event> event) override;
    void draw(sf::RenderWindow& window) override;

    // m.0d (Setters/Getters for the spec fields)
    void                set_spec_0(bool spec0) override { _spec_0 = spec0; }
    virtual void        set_spec_1(std::string s1)      { __spec_1 = s1;   }
    bool                get_spec_0() override           { return _spec_0;  }
    virtual std::string get_spec_1()                    { return __spec_1; }

    // m.0e (Setters/Getters for other internal fields)
    void  set_private_field  (int val0)     { __private_field = val0;    }
    void  set_protected_field(float value1) { _protected_field = value1; }
    int   get_private_field  ()             { return __private_field;    }
    float get_protected_field()             { return _protected_field;   }

    // m.0f (Linkers for the callbacks)
    void link_on_mouse_click  (CALLBACK_BOOL callback) override;
    void link_on_mouse_release(CALLBACK_BOOL callback) override;
    void link_on_mouse_move   (CALLBACK_BOOL callback) override;
    void link_on_key_press    (CALLBACK_BOOL callback) override;

    // m.0g (Other functionalities)
    bool some_public_functionality();

protected:
    // m.1a (Internal functionalities)
    void _some_internal_functionality();

    // m.1b (Callback wrappers)
    bool _internal_on_mouse_click  (const std::optional<sf::Event> event) override;
    bool _internal_on_mouse_release(const std::optional<sf::Event> event) override;
    bool _internal_on_mouse_move   (const std::optional<sf::Event> event) override;
    bool _internal_on_key_press    (const std::optional<sf::Event> event) override;

    // d.1a (Static fields)
    static std::unordered_map<
        std::string, std::vector<nd::Widget*>
    > _some_protected_table; // init in the .cpp file

    // d.1b (Spec fields)
    bool _spec_0 = false;

    // d.1c (Client callbacks)
    CALLBACK_BOOL _on_mouse_click;
    CALLBACK_BOOL _on_mouse_release;
    CALLBACK_BOOL _on_mouse_move;
    CALLBACK_BOOL _on_key_press;

    // d.1d (Other fields)
    float _protected_field = 0.0f;

private:
    // m.2a (Internal functionalities)
    void __some_private_functionality();

    // d.2a (Static fields)
    static std::unordered_map<std::string, int> __some_private_table; // init in the .cpp file

    // d.2b (Spec fields)
    std::string __spec_1 = "";

    // d.2c (Other fields)
    int __private_field = 0;
};
```
