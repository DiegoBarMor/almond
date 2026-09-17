# Changelog

## [0.4.0] - 2026-09-17
- Refactored event management.
    - Introduced the `nd::Event` union as a wrapper for SFML events (motivation: syntactic sugar for the user's on_event callbacks).
    - Introduced the `nd::EventType` enum to identify the types of events.
    - Widgets now have a single generic `on_event` callback, where conditional statements are to be placed inside to control the management of different event types.
        - Some widget subclasses still hold specialized event management callbacks e.g. `on_click` for button widgets.
    - The app instance can now also handle events in a similar manner, via a generic `on_event` callback.
        - Useful for callbacks that aren't really linked to any widget, like *closed* events.
        - Note that this callback is processed before the widget callbacks.

- Internal code improvements.
    - Replaced raw pointers with smart pointers.
    - More setters/getters now deal with const references instead of by copying.
    - Some other cleanups and reorganizations.
    - Renamed `sf::WidgetManager` to `sf::DrawableManager` (anticipating future changes).


## [0.3.1] - 2026-07-29
- Added getter/setter for `sf::WidgetManager::__font` (useful for creating custom widgets that need fonts).


## [0.3.0] - 2026-07-28
- ALMOND now statically links to a global installation of SFML (instead of each almond project building it locally).
    - CMake usage was also replaced with bash scripts.
- ALMOND is now packed into a single header before compilation.
- Adjusted several aspects of the widgets API.
- Several refactorings and reorganizations of the code.


## [0.2.0] - 2026-07-25
- Replaced all occurances of static objects in the code with alternative implementations.


## [0.1.0] - 2026-07-13
- Migrated ALMOND from SFML `2.5.1` to SFML `3.1.0`.
