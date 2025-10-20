/*#include <SFML/Graphics.hpp>
#define _WIN32_WINNT 0x0500
#include <Windows.h>*/
 
//int main()
//{
//	HWND hWnd = GetConsoleWindow();//берем текущ консоль, (скрывает консоль (работает только под windows))
//	ShowWindow(hWnd, SW_HIDE);//скрывает консоль
//	return 0;
//}

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <conio.h>
#include <math.h>
#include "Tank.h"
#include "SpeedMeter.h"
#include "Bullet.h"
#include "TMap.h"

using namespace std; 
using namespace sf;

#define areaW 30
#define areaH 24
#define maxSpeed 2000

RenderWindow window(VideoMode(1200,650),"Game window",sf::Style::Default);

float CTank::mSpeed=maxSpeed;

float offsetX=0,offsetY=0;

RenderWindow *CBullet::wind=&window;
CBullet::bul *CBullet::head=NULL;

RenderWindow *CTank::wind=&window;

String TLMap[areaH] = {
	/*"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"B1111111111111BB1111111111111B",
	"B             BB    P        B",
	"B     P       BB             B",
	"B    23332    11    23332    B",
	"B    45554          45554    B",
	"B    45554          45554    B",
	"B    45554    BB    45554    B",
	"B    23332    BB    23332    B",
	"B             BB  P      P   B",
	"B            B11B            B",
	"B           B1551B           B",
	"BBBBBB   BBB155551BBB   BBBBBB",
	"B11111   111B5555B111   11111B",
	"B           1B55B1P          B",
	"B     P      1BB1            B",
	"B    23332    11    23332 P  B",
	"B    45554 P     P  45554    B",
	"B    45554          45554    B",
	"B    45554    BB    45554  P B",
	"B   P23332   B11B   23332    B",
	"B           B1  1B           B",
	"BBBBBBBBBBBB1    1BBBBBBBBBBBB",
	"111111111111      111111111111",*/
	"BBBBBBBBBBBBBBBB              ",
	"B6111111111111BB              ",
	"B             BB              ",
	"B     P       BB              ",
	"B    23332    BB       B      ",
	"B    45554    BB      BBB     ",
	"B    45554    BB     BBBBB    ",
	"B    45554    BB    BBBBBBB   ",
	"B    23332    BB     BBBBB    ",
	"B             BB      BBB     ",
	"B            B11B      B      ",
	"B           B1551B            ",
	"BBBBBB   BBB155551BBBBBB  BBBB",
	"B11111   111B5555B111111n 111B",
	"B           1B55B1P          B",
	"B     P      1BB1            B",
	"B    23332    11    23332 P  B",
	"B    45554 P     P  45554    B",
	"B    45554          45554    B",
	"B    45554    BB    45554  P B",
	"B   P23332   B11B   23332    B",
	"B           B1  1B           B",
	"BBBBBBBBBBBB1    1BBBBBBBBBBBB",
	"111111111111      111111111111",

};

RenderWindow *CTMap::wind=&window;
String *CTMap::TileMap=TLMap;
int CTMap::width=areaW;
int CTMap::height=areaH;
float CTMap::offsetX=0;
float CTMap::offsetY=0;

float scalarV(float x1,float y1,float x2,float y2)
{
	return (x1*x2)+(y1*y2);
}

float modV(float x,float y)
{
	return pow(pow(x,2)+pow(y,2),1./2.);
}

float count_angle(float cx,float cy,float x1,float y1)
{
	if(x1-cx>=0)
		return acosf(scalarV(0,-1,x1-cx,y1-cy)/(modV(0,-1)*modV(x1-cx,y1-cy)))*180/3.14;
	else
		return 360-(acosf(scalarV(0,-1,x1-cx,y1-cy)/(modV(0,-1)*modV(x1-cx,y1-cy)))*180/3.14);
}

int cSym(float num)
{
	int k=0;
	while(num>1)
	{
		num/=10;
		k++;
	}
	return k;
}



void coutT(RenderWindow &wind,char *text,Font font,unsigned int size,float angle,float origin1,float origin2,float x,float y)
{
	Text txt;
	txt.setCharacterSize(size);
	txt.setFont(font);
	txt.setPosition(x,y);
	txt.setString(text);
	txt.setRotation(angle);
	txt.setOrigin(Vector2f(origin1,origin2));
	wind.draw(txt);
}

void main()
{
	Font font;
	font.loadFromFile("Dynar-Medium.ttf");
	Texture tex;
	tex.loadFromFile("image.png");
	Clock clock;
	CTank car(tex);
	//RectangleShape speedMeter;
	CSpeedMeter speedMeter(&window,font,&car,window.getSize().x-125,window.getSize().y-125,2000);
	//CTMap tMap(TileMap,areaW,areaH);
	int wind_active=1;
	float generalTime=0;
	//cout<<"|cos="<<cos(60)<<"|"<<cos(180/(60*3.14))<<"|";
	while(window.isOpen())
	{
		float time= clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time=time/1000;
		cout<<"|TIME="<<time<<"|"<<endl;
		Event event;
		while(window.pollEvent(event))
		{
			if((event.type == Event::Closed)||(Keyboard::isKeyPressed(Keyboard::Escape)))
				window.close();
			if(event.type == sf::Event::GainedFocus)
			{
				wind_active=1;
				cout<<"wind_active set to 1\n";
			}
			if(event.type == sf::Event::LostFocus)
			{
				wind_active=0;
				cout<<"wind_active set to 0\n";
			}
		}
		if((!wind_active)||(time>0.1))
			continue;
		window.clear(Color::Color(128,128,128,255));
		CTMap::draw(offsetX,offsetY);
		car.update(time);
		window.draw(car.getSprite());
		speedMeter.update();
		CBullet::update(time);
		window.display();
		generalTime+=time;
		float rX=car.getRect().left,rY=car.getRect().top;
		/*if((p.rect.left>(WindowWidth*32)/2)&&(p.rect.left<(W*32)-(WindowWidth*32)/2)) offsetX=p.rect.left-(WindowWidth*32)/2;
		if((p.rect.top>(WindowHeight*32)/2)&&(p.rect.top<(H*32)-(WindowHeight*32)/2)) offsetY=p.rect.top-(WindowHeight*32)/2;*/
		//if((rX>window.getSize().x*64/2)&&(rX<(areaW*64)-(window.getSize().x*64)/2))
		if(rX>window.getSize().x/2)
			offsetX=rX-window.getSize().x/2;
		if(rY>window.getSize().y/2)
			offsetY=rY-window.getSize().y/2;
		//cout<<"|ofX="<<offsetX<<"|"<<endl;
		//offsetY+=areaH-rY*2;
	}
}