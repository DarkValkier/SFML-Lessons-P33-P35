#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button: public sf::RectangleShape
{
public:
	std::function<void(Button&)> onclick;
	Button(sf::Vector2f _position, sf::Vector2f _size);
};

