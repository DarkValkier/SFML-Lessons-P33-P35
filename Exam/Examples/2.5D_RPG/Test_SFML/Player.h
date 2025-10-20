#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class CPLAYER
{
public:
	float dx,dy;
	FloatRect rect;
	Texture texture;
	Sprite sprite;
	float curFrame;
	int dir;
	int r,g,b;
	CPLAYER::CPLAYER(Texture &image);
	void update(float time);
	void Collision(char f);
	void keyboardCheck();
};