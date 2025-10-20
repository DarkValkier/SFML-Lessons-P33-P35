#pragma once
#include "Tank.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class CSpeedMeter
{
	RectangleShape arrow;
	Texture SMTexture;
	Sprite SMCircle;
	RenderWindow *wind;
	Font font;
	CTank *tank;
	float x,y;
	float speed,mSpeed;
public:
	CSpeedMeter(RenderWindow *,Font,CTank *,float,float,float);
	~CSpeedMeter(void);
	void update();
};

