#pragma once
#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;

class Map
{
	Vector2i size = {10, 5};
	Vector2i tileSize = { 70, 70 };
	char** map;
	Texture txTiles;

	void allocateMemoryForMap();
	void freeMemoryForMap();

public:
	Map();
	Map(Vector2i, Vector2i, const char*);
	~Map();

	void draw(RenderWindow&);
	Vector2f getSeparationVector(FloatRect, FloatRect);
	void checkCollisions(Sprite& player);

	void printMap();
};

