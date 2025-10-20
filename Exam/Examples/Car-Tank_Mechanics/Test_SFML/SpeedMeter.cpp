#include "SpeedMeter.h"
#include "Tank.h"


CSpeedMeter::CSpeedMeter(RenderWindow *iWind,Font iFont,CTank *iTank,float ix,float iy,float maxSpeed)
{
	x=ix;
	y=iy;
	arrow.setSize(Vector2f(30,3));
	arrow.setOrigin(0,1.5);
	arrow.setPosition(x,y);
	arrow.setFillColor(Color::White);
	SMTexture.loadFromFile("SpeedMeter.png");
	SMCircle.setTexture(SMTexture);
	SMCircle.setTextureRect(IntRect(0,0,150,150));
	SMCircle.setOrigin(75,75);
	SMCircle.setPosition(x,y);
	speed=0;
	
	mSpeed=maxSpeed;
	wind=iWind;
	font=iFont;
	tank=iTank;
}


CSpeedMeter::~CSpeedMeter(void)
{
}

void CSpeedMeter::update()
{
	wind->draw(SMCircle);
	arrow.setRotation((fabs(tank->getSpeed())*270/mSpeed)-225);
	wind->draw(arrow);
	float yBuf=-(cos((arrow.getRotation()+90)*3.14/180)*60)+y;
	float xBuf=cos(fabs(float(arrow.getRotation()))*3.14/180)*60+x;
	char text[256];
	itoa(fabs(tank->getSpeed()/10),text,10);
	Text txt;
	txt.setCharacterSize(14);
	txt.setFont(font);
	txt.setPosition(xBuf,yBuf);
	txt.setString(text);
	txt.setOrigin(Vector2f(4*strlen(text),10));
	wind->draw(txt);
	if(tank->getReload()<100)
	{
		RectangleShape reload;
		reload.setFillColor(Color::Color(int((100-tank->getReload())*2.55),int((tank->getReload())*2.55),0,255));
		reload.setSize(Vector2f(tank->getReload(),10));
		reload.setPosition(tank->getRect().left-50-CTMap::getOffset().x,tank->getRect().top-100-CTMap::getOffset().y);
		reload.setOutlineColor(Color::Black);
		reload.setOutlineThickness(1);
		wind->draw(reload);
	}
}