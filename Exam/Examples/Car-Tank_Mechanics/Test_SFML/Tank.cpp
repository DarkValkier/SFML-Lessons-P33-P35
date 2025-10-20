#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <conio.h>
#include <math.h>

#include "Tank.h"
#include "Bullet.h"

using namespace std; 
using namespace sf;

void CTank::checkSpeed(float time)
{
	if((Keyboard::isKeyPressed(Keyboard::W))&&(speed<mSpeed))
	{
		if(Keyboard::isKeyPressed(Keyboard::E))
		{
			speed+=(speed*speed)*time;
			//cout<<"W";
			return;
		}
		else
		{
			speed+=100*time;
			//cout<<"W";
			return;
		}
	}
	if((Keyboard::isKeyPressed(Keyboard::S))&&(speed>-mSpeed/2))
	{
		speed-=70*time;
		//cout<<"S";
		return;
	}
	if((speed<10)&&(speed>-10))
	{
		speed=0;
		return;
	}
	if(speed>10)
	{
		speed-=speed*0.1*time;
		return;
	}
	if(speed<-10)
	{
		speed+=speed*0,1*time;
		return;
	}
}
void CTank::lowSpeed(int am)
{
	if(speed>1)
	{
		speed-=am;
		if(speed<0)
			speed=0;
		return;
	}
	if(speed<-1)
	{
		speed+=am;
		if(speed>0)
			speed=0;
	}

}
CTank::CTank(Texture &image)
{
	sprite.setTexture(image);
	//sprite.setColor(Color::White);
	rect=FloatRect(128,200,50,50);
	sprite.setTextureRect(IntRect(0,0,50,50));
	sprite.setOrigin(rect.width/2,rect.height/2);
	speed=0;
	angle=0;
	reload=0;
	pReload=100.;
	loadBullet=0;
	hp=100;
}

CTank::~CTank()
{

}
void CTank::update(float time)
{
	checkSpeed(time);
	if(Keyboard::isKeyPressed(Keyboard::D))
	{
		angle+=45*time;
		if(angle>360)
			angle=0;
	}
	if(Keyboard::isKeyPressed(Keyboard::A))
	{
		angle-=45*time;
		if(angle<0)
			angle=360;
	}
	float yBuf=-(cos(angle*3.14/180)*speed);
	if(!CTMap::checkCollision(rect.left,rect.top+yBuf*time))
	{
		rect.top+=yBuf*time;
		
	}
	else
		lowSpeed(70);
	//float xBuf=cos((fabs(angle-90))*3.14/180)*speed;
	float xBuf=sin(angle*3.14/180)*speed;
	if(!CTMap::checkCollision(rect.left+xBuf*time,rect.top))
	{
		rect.left+=xBuf*time;
	}
	else
		lowSpeed(70);
	if(pReload<100)
		pReload+=100/reload*time;
	if(pReload>=100)
		pReload=100;
	if(Keyboard::isKeyPressed(Keyboard::B))
	{
		rect.left=rect.top=32;
	}
	if(Keyboard::isKeyPressed(Keyboard::LControl))
	{
			lowSpeed(fabs(2000/speed));
	}
	if((Keyboard::isKeyPressed(Keyboard::Space))&&(pReload==100))
		{
			float bSpeed=1000;
			if(speed>0)
				bSpeed+=speed;
			CBullet::createBullet(loadBullet,rect.left+cos((fabs(angle-90))*3.14/180)*50,rect.top-(cos(angle*3.14/180)*50),angle,bSpeed);
			reload=2;
			if(loadBullet==3)
				reload=0.2;
			pReload=0;
		}
	if(Keyboard::isKeyPressed(Keyboard::F1))
		loadBullet=0;
	if(Keyboard::isKeyPressed(Keyboard::F2))
		loadBullet=1;
	if(Keyboard::isKeyPressed(Keyboard::F3))
		loadBullet=2;
	if(Keyboard::isKeyPressed(Keyboard::F4))
		loadBullet=3;
	//int d=(pow(2,1./2.)*50-50);
	/*if(rect.left>wind->getSize().x+50)
		rect.left=-50;
	if(rect.left<-50)
		rect.left=wind->getSize().x+50;
	if(rect.top>wind->getSize().y+50)
		rect.top=-50;
	if(rect.top<-50)
		rect.top=wind->getSize().y+50;*/
	//sprite.setTextureRect(IntRect(rect));
	sprite.setRotation(angle);
	sprite.setPosition(rect.left-CTMap::getOffset().x,rect.top-CTMap::getOffset().y);
	//sprite.setScale(2,2);
}
Sprite CTank::getSprite()
{
	return sprite;
}
float CTank::getSpeed()
{
	return speed;
}
float CTank::getAngle()
{
	return angle;
}
FloatRect CTank::getRect()
{
	return rect;
}
float CTank::getReload()
{
	return pReload;
}
