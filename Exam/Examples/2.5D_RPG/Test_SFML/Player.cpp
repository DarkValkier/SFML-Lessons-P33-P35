#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>

/*CPLAYER::CPLAYER(Texture &image)
{
	sprite.setTexture(image);
	rect=FloatRect(32,32,32,48);
	curFrame=0;
	dir=0;
	sprite.setTextureRect(IntRect(32*int(curFrame)+32,48*dir,32,48));
	float x,y;
	if((rect.left>(WindowWidth*32)/2)&&(rect.left<(W*32)-(WindowWidth*32)/2)) 
	{
		offsetX=rect.left-(WindowWidth*32)/2;
		x=(WindowWidth*32)/2;
	}
	else
		x=rect.left;
	if((rect.top>(WindowHeight*32)/2)&&(rect.top<(H*32)-(WindowHeight*32)/2)) 
	{
		offsetY=rect.top-(WindowHeight*32)/2;
		y=(WindowHeight*32)/2;
	}
	else
		y=rect.top;
	sprite.setPosition(x,y);
	dx=dy=0;
	r=g=b=255;
}
void CPLAYER::update(float time)
{
	if(wind_active)
		keyboardCheck();
	// Движение персонажа
	rect.left+=dx*time;
	Collision('x');
	rect.top+=dy*time;
	Collision('y');

	if((dx!=0)||(dy!=0))
	{
		curFrame+=0.005*time;
		if(curFrame > 3) curFrame-=3;
		sprite.setTextureRect(IntRect(32*int(curFrame)+32,48*dir,32,48));
		sprite.setPosition(rect.left-offsetX,rect.top-offsetY);
		dx=0;
		dy=0;
	}*/
	/*if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))&&(wind_active))
	{
	if(r>0) r=g=b=r-1;
	sprite.setColor(sf::Color::Color(r,g,b,255));
	cout<<"r="<<r;
	}
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Right))&&(wind_active))
	{
	if(r<255) r=g=b=r+1;
	sprite.setColor(sf::Color::Color(r,g,b,255));
	cout<<"r="<<r;
	}*/
/*}
void CPLAYER::Collision(char f)
{
	for(int i=rect.top/32;i<(rect.top+rect.height)/32;i++)
		for(int j=rect.left/32;j<(rect.left+rect.width)/32;j++)
		{
			if(TileMap[i][j]=='B')
			{
				//cout<<"a";
				if((dx>0)&&(f=='x')) rect.left= j*32 - rect.width;
				if((dx<0)&&(f=='x')) rect.left= j*32 + 32;
				if((dir==0)&&(f=='y')) rect.top= i*32 - rect.height;
				if((dir==3)&&(f=='y')) rect.top= i*32 + 32;
			}
			if(TileMap[i][j]=='P')
			{
				TileMap[i][j]=' ';
			}
		}
}
void CPLAYER::keyboardCheck()
{
	// Проверка клавиш
	if(Keyboard::isKeyPressed(Keyboard::Left))
	{
		dir=1;
		dx=-0.1;
	}
	if(Keyboard::isKeyPressed(Keyboard::Right))
	{
		if(Keyboard::isKeyPressed(Keyboard::Left))
		{
			dx=0;
		}
		else
		{
			dir=2;
			dx=0.1;
		}
	}
	if(Keyboard::isKeyPressed(Keyboard::Up))
	{
		dir=3;
		dy=-0.1;
	}
	if(Keyboard::isKeyPressed(Keyboard::Down))
	{
		if(Keyboard::isKeyPressed(Keyboard::Up))
		{
			dy=0;
		}
		else
		{
			dir=0;
			dy=0.1;
		}
	}
	if((dx!=0)&&(dy!=0))
	{
		dx=dx-dx/4;
		dy=dy-dy/4;
	}
}*/