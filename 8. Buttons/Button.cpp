#include "Button.h"

Button::Button(sf::Vector2f _position, 
	sf::Vector2f _size)
{
	setSize(_size);
	setPosition(_position);
	setFillColor(sf::Color::Green);
}