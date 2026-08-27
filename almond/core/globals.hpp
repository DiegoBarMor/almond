#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#define OLD_CALLBACK_BOOL std::function<bool(const std::optional<sf::Event>)>
#define CALLBACK_BOOL std::function<bool()>
#define CALLBACK_VOID std::function<void()>
