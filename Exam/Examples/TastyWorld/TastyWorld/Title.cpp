#include "Title.h"

void CTitle::drawText(Vector2f i_pos,String i_text,RenderWindow *i_wind)
{
	// === Вывод текста на кнопке ===
	tTitle.setString(i_text);
	tTitle.setOrigin(Vector2f(11.5*i_text.getSize(),30));
	// -- Вывод тени --
	tTitle.setPosition(i_pos.x+3,i_pos.y+3);
	tTitle.setColor(Color::Black);
	i_wind->draw(tTitle);
	// -- Вывод основного текста --
	tTitle.setPosition(i_pos.x,i_pos.y);
	tTitle.setColor(tColor);
	i_wind->draw(tTitle);
}

void CTitle::loadData()
{
	tFont.loadFromFile("data/Fonts/9914.ttf");
	tTitle=Text("",tFont,48);
	tColor=Color::Yellow;
	tTitle.setColor(tColor);
	tTitle.setStyle(Text::Regular);
	vColor=Color(0,0,0,0);
	vDColor=Color(0,0,0,0);

	a=VertexArray(sf::Quads,4);

	a[0].color=vColor;
	a[1].color=vColor;
	a[2].color=Color::Color(0,0,0,0);
	a[3].color=vColor;

	a[2].position=Vector2f(400,300);

}

void CTitle::setVignette(Color i_color)
{
	vColor=i_color;
}

void CTitle::resetVignette()
{
	vDColor=Color(0,0,0,0);
}

void CTitle::drawVignette(RenderWindow *wind,float i_time)
{
	vDColor=Color(vDColor.r+(vColor.r-vDColor.r)*i_time*2,vDColor.b+(vColor.b-vDColor.b)*i_time*2,vDColor.g+(vColor.g-vDColor.g)*i_time*2,vDColor.a+(vColor.a-vDColor.a)*i_time*2);
	if(vDColor.a==0)
		return;
	a[0].color=vDColor;
	a[1].color=vDColor;
	a[2].color=Color::Color(0,0,0,0);
	a[3].color=vDColor;

	a[0].position=Vector2f(0,0);
	a[1].position=Vector2f(400,0);
	a[3].position=Vector2f(0,300);

	wind->draw(a);

	a[0].position=Vector2f(800,0);
	a[3].position=Vector2f(800,300);

	wind->draw(a);

	a[0].position=Vector2f(800,600);
	a[1].position=Vector2f(400,600);

	wind->draw(a);

	a[0].position=Vector2f(0,600);
	a[3].position=Vector2f(0,300);

	wind->draw(a);

}

CTitle::CTitle(void)
{
}


CTitle::~CTitle(void)
{
}
