#pragma once
#include "main.h"

class ButtonsBase
{
protected:
	struct ButtonNode
	{
		Vector2f position;
		String title;
		int index;
		bool isHover;
		bool isActive;
	};
	vector<ButtonNode> btnList; //Список кнопок
	Font btnFont; //Шрифт текста над кнопками
	Text btnTitle;//Параметры текста над кнопками
	Sprite btnSprite;//Спрайт кнопки
	Texture btnTexture;//Текстура кнопки
	int clickedBtn;//Индекс нажатой кнопки (по умолчанию -1)
	bool isButtonHold[2];//Отслеживание нажатия левой клавиши мыши (не нажата, нажата, зажата)

	void loadBaseData();//Загрузка базовых данных
	void chechMouse();//Проверка левой кнопки мыши и обнуление нажатой кнопки
	void drawText(unsigned int i_num,Vector2f btnPos,RenderWindow *i_wind);//Вывод текста над кнопкой
public:
	int getClick();//Проверка нажатой кнопки
	virtual void update(RenderWindow *i_wind) = 0;//Обновление кнопок
	virtual void draw(RenderWindow *i_wind) = 0;//Вывод кнопок на экран
	ButtonsBase(void);
	virtual ~ButtonsBase(void);
};

