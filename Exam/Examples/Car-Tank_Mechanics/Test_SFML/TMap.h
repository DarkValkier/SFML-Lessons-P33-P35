#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class CTMap
{
	static String *TileMap;
	static int width,height;
	static float offsetX,offsetY;
	static RenderWindow *wind;
public:
	static void draw(float ofX,float ofY);
	static int checkCollision(float x,float y);
	static Vector2f getOffset();
	CTMap();
	~CTMap(void);
};

