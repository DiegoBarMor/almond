#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#define CALLBACK_EVENT std::function<bool(const nd::Event& event)>
