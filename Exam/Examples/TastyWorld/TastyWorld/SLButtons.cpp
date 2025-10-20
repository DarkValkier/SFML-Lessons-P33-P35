#include "SLButtons.h"
#include <stdio.h>

void SLButtons::update(RenderWindow *i_wind)
{
	chechMouse();
	Vector2i mPos=Mouse::getPosition(*i_wind);
	// === Проверка мыши ===
	for(int i=0;i<btnList.size();i++)
	{
		if(!btnList[i].isActive)
			continue;
		if( pow(pow(mPos.x-btnList[i].position.x,2)+pow(mPos.y-btnList[i].position.y,2),1./2.) <= btnParList[i].radius )
			if((Mouse::isButtonPressed(Mouse::Button::Left))&&!isButtonHold[1])
			{
				btnList[i].isHover = false;
				if((clickedBtn== -1) || (clickedBtn>btnList[i].index))
					clickedBtn = btnList[i].index;
			}
			else
			{
				btnList[i].isHover = true;
			}
		else
		{
			btnList[i].isHover = false;
		}
	}
	if(isButtonHold[0]&&!isButtonHold[1])
	{
		ostringstream mes;
		mes<<"Button with index "<<clickedBtn<<" has been clicked!";
		sendToLog("SLButtons",mes.str());
	}
}
void SLButtons::draw(RenderWindow *i_wind)
{
	for(int i=0;i<btnList.size();i++)
	{
		CircleShape slBtn;
		if(!btnList[i].isActive)
			slBtn.setFillColor(Color::Color(120,120,120,255));
		else
			if(btnList[i].isHover)
				slBtn.setFillColor(Color::Color(100,100,255,255));
			else
				slBtn.setFillColor(Color::Blue);
		slBtn.setRadius(btnParList[i].radius);
		slBtn.setPosition(btnList[i].position);
		slBtn.setOrigin(btnParList[i].radius,btnParList[i].radius);
		i_wind->draw(slBtn);		
		drawText(i,btnList[i].position,i_wind);
	}
	
}

void SLButtons::addButton(Vector2f i_coord,float i_radius,String i_title,int i_index,String i_way,bool i_active)
{
	//=== Создание новой кнопки ===
	ButtonNode newBtn;
	newBtn.position = Vector2f(i_coord.x,i_coord.y);
	newBtn.title = i_title;
	newBtn.index = i_index;
	newBtn.isHover = false;
	newBtn.isActive = i_active;
	btnList.push_back(newBtn);

	//=== Создание доп. параметров новой кнопки ===
	ButtonParameters newPar;
	newPar.radius = i_radius;
	newPar.way = i_way;
	btnParList.push_back(newPar);

	//=== Запись в лог ===
	ostringstream mes;
	mes<<"Added new level button with index "<<i_index<<"!";
	sendToLog("SLButtons",mes.str());
}

void SLButtons::removeAllButtons()
{
	btnList.clear();
	btnParList.clear();
}

String SLButtons::getWay()
{
	for(int i=0;i<btnList.size();i++)
	{
		if(btnList[i].index==clickedBtn)
			return btnParList[i].way;
	}
	return "";
}

void SLButtons::loadData()
{
	btnTexture.loadFromFile("Data/Textures/Interface/buttons.png");
	btnSprite.setTexture(btnTexture);
}

SLButtons::SLButtons(void)
{
	loadData();
}


SLButtons::~SLButtons(void)
{
	removeAllButtons();
}
