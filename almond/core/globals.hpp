#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#define CALLBACK_BOOL std::function<bool(const std::optional<sf::Event>)>
#define CALLBACK_VOID std::function<void()>
#define INTERSECTS_MOUSE(pos) contains_point(sf::Vector2f((float)pos.x, (float)pos.y))
