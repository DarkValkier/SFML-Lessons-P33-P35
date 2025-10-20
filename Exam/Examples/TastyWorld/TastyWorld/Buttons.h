#pragma once
#include "main.h"
#include "ButtonsBase.h"

class CButtons:public ButtonsBase
{
public:
	enum btnAlignX
	{
		left,
		centerX,
		right
	};
	enum btnAlignY
	{
		top,
		centerY,
		bottom
	};
	struct ButtonParameters
	{
		Vector2f size;
		btnAlignX alX;
		btnAlignY alY;
	};
private:
	vector<ButtonParameters> btnParList; //Параметры кнопок

	Vector2f countBtnPos(unsigned int i_num,RenderWindow *i_wind);
public:
	void addButton(FloatRect i_coord,btnAlignX i_alX,btnAlignY i_alY,String i_title,int i_index,bool i_active);//Добавление кнопки
	void removeAllButtons();
	void update(RenderWindow *i_wind);
	void draw(RenderWindow *i_wind);
	void loadData();
	CButtons(void);
	~CButtons(void);
};
