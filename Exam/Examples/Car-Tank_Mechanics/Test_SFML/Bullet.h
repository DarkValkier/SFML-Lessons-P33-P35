#pragma once

#include <SFML/Graphics.hpp>
#include "TMap.h"

using namespace sf;

class CBullet
{
	struct bul
	{
		float angle,speed;
		float x,y;
		float clock;
		int type;
		bool alive;
		bul *next;
	};
public:
	static RenderWindow *wind;
	static bul *head;
	static void update(float);
	static void createBullet(int,float,float,float,float);
	static void clearNodeBullet();
	static void deleteNodeBullet();
	static void displayNodeBullet();
	CBullet();
	~CBullet(void);
};

