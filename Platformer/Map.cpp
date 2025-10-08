#include "Map.h"
#include <iostream>

Map::Map() :size({10, 5})
{
	allocateMemoryForMap();
	txTiles.loadFromFile("tiles_spritesheet.png");
}

Map::Map(Vector2i _size, Vector2i _tileSize, 
	const char* _map):size(_size), tileSize(_tileSize)
{
	allocateMemoryForMap();
	for (int y = 0; y < size.y; y++)
		for (int x = 0; x < size.x; x++)
			map[y][x] = _map[y * size.x + x];
	txTiles.loadFromFile("tiles_spritesheet.png");
	printMap();
}

Map::~Map()
{
	freeMemoryForMap();
}

void Map::allocateMemoryForMap()
{
	map = new char* [size.y];
	for (int row = 0; row < size.y; row++)
		map[row] = new char[size.x];
}

void Map::freeMemoryForMap()
{
	for (int row = 0; row < size.y; row++)
		delete[] map[row];
	delete[] map;
}

void Map::draw(RenderWindow& window)
{
	std::map<char, Sprite> spriteSheet = {
		{'G', Sprite(txTiles, IntRect({ 72 * 9, 0 }, { 70, 70 }))},
		{'B', Sprite(txTiles, IntRect({ 0, 72 * 11 }, { 70, 70 }))},
		{'L', Sprite(txTiles, IntRect({0, 72 * 2}, {70, 70}))},
	};

	for (int y = 0; y < size.y; y++)
		for (int x = 0; x < size.x; x++)
		{
			auto spriteIt = spriteSheet.find(map[y][x]);
			if (spriteIt != spriteSheet.end())
			{
				spriteIt->second.setPosition(
					{ (float)(x * tileSize.x), 
					(float)(y * tileSize.y) }
				);
				window.draw(spriteIt->second);
			}
		}
}

Vector2f Map::getSeparationVector(FloatRect rect1, FloatRect rect2)
{
	Vector2f separationVector = { 0.f, 0.f };
	auto intersection = rect1.findIntersection(rect2);
	if (intersection.has_value())
	{
		FloatRect intersectionRect = intersection.value();
		if (intersectionRect.size.x < intersectionRect.size.y)
			if (rect1.position.x < rect2.position.x)
				separationVector = { -intersectionRect.size.x, 0.f };
			else
				separationVector = { intersectionRect.size.x, 0.f };
		else
			if (rect1.position.y < rect2.position.y)
				separationVector = { 0.f, -intersectionRect.size.y };
			else
				separationVector = { 0.f, intersectionRect.size.y };
	}
	return separationVector;
}

void Map::checkCollisions(Sprite& player)
{
	FloatRect playerRect = player.getGlobalBounds();
	Vector2f totalVector = { 0.f, 0.f };
	for (int y = 0; y < size.y; y++)
		for (int x = 0; x < size.x; x++)
			if (map[y][x] != ' ')
			{
				FloatRect tileRect = FloatRect(
					{ (float)(x * tileSize.x), (float)(y * tileSize.y) },
					{ (float)tileSize.x, (float)tileSize.y });
				totalVector += getSeparationVector(playerRect, tileRect);
			}
	player.move(totalVector);
}

void Map::printMap()
{
	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
			if (map[y][x] != ' ')
				std::cout << map[y][x];
			else
				std::cout << '.';
		std::cout << std::endl;
	}
}
