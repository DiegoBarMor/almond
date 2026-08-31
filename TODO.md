# TODO

## Priority
- Replace raw pointers with smart pointers

## Implementations / Improvements
- Implement more widget types:
    - `nd::Slider`.
    - `nd::GridLayout`.
    - `nd::ScrollLayout`.
    - `nd::Draggable`.
- Improve the `nd::TextInput`
    - Add cursor, capable of moving around when using the arrows and selecting sections of text. Clipboard operations should behave differently when a selection is active.
    - Add spec to enable or disable multiline.
- Define a small `nd::RectShapeOverlay` class (not a widget) that can be used by `nd::CheckBox`, `nd::RadioButton` and `nd::TextInput`.
- Add a global resource for assigning default colors to the widgets, instead of hardcoding them in every class.
- Add possibility to escape characters in a text spec.
- Add possibility to swap out widgets (including the root) at runtime, either by giving the reference to an existing object, or by parsing it from a `NDG` file.
    - Implement appropriate destructors, for when widgets are removed.
    - Consider using a linked list approach instead of the RadioButtonGroup structs. This will allow for better managing when adding/deleting radiobuttons.
- Implement text alignment spec for `nd::Text`
- Allow to specify vertical and horizontal padding separately.
- Add back the option to use CMake for a local installation (let the user decide).

## Issues
- Fix the click detection after the window changes shape/size.
- Check why `nd::Text` instances with larger font sizes don't align properly their `sf::Text` field.
- Fix implementation issue where buttons can be activated by pressing click outside and then simply releasing it inside its boundaries.
- Fix button not changing color from hover to idle state if the mouse gets into another window.
- Check why widgets square-forced widgets in a container are sometimes smaller at the ends of the container.
- Allow empty containers (instead of breaking the parser).

## Documentation
- Document the event types and the event management.
- Document properly the lifecycle of the App instances: init, create, build...
- Document the specs.
