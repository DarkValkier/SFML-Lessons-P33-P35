#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
class CTitle
{
public:
	static Font tFont;
	static Text tTitle;
	static Color tColor;
	static Color vColor;
	static Color vDColor;
	static VertexArray a;
	static void drawText(Vector2f i_pos,String i_text,RenderWindow *i_wind);
	static void drawVignette(RenderWindow *wind,float i_time);
	static void setVignette(Color i_color);
	static void resetVignette();
	static void loadData();
	CTitle(void);
	~CTitle(void);
};

