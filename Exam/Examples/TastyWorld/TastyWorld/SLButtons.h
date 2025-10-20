#pragma once
#include "main.h"
#include "ButtonsBase.h"

class SLButtons:public ButtonsBase
{
public:
	struct ButtonParameters
	{
		float radius;
		String way;
	};
private:
	vector<ButtonParameters> btnParList; //Параметры кнопок
public:
	void addButton(Vector2f i_coord,float i_radius,String i_title,int i_index,String i_way,bool i_active);//Добавление кнопки
	void removeAllButtons();
	String getWay();
	void update(RenderWindow *i_wind);
	void draw(RenderWindow *i_wind);
	void loadData();
	SLButtons(void);
	~SLButtons(void);
};
