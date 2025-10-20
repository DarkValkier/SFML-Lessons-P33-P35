#pragma once
#include "TMap.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class CTank
{
	FloatRect rect;
	Texture texture;
	Sprite sprite;
	float speed,angle,reload,pReload,hp;
	int loadBullet;
	void checkSpeed(float time);
	void lowSpeed(int am);
public:
	static RenderWindow *wind;
	static float mSpeed;
	CTank(Texture &image);
	~CTank();
	void update(float time);
	Sprite getSprite();
	float getSpeed();
	float getAngle();
	FloatRect getRect();
	float getReload();
};