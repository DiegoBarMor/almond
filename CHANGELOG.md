# Changelog

## [0.3.1] - 2026-07-29
- Added getter/setter for `sf::ManagerDrawables::__font` (useful for creating custom widgets that need fonts).

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
