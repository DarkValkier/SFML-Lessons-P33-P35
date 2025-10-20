#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
#include "Shape.h"

#define objFile "kub.txt"

using namespace sf;
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600), "Graphic LR 2");

	//window.setMouseCursorVisible(false);
	cout<<" Enter path to the file:";
	char inp_file[256]={'\0'};
	cin>>inp_file;
	CShape letter;
	if(inp_file[0]=='\0')
		letter=CShape(objFile,Vector3f(400.f,300.f,1000.f),Vector2f(800,600));
	else
		letter=CShape(inp_file,Vector3f(400.f,300.f,1000.f),Vector2f(800,600));
	sf::Clock timer;

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == Event::MouseWheelScrolled)
				letter.scaleCam(event.mouseWheelScroll.delta*0.1);
		}

		if(Keyboard::isKeyPressed(Keyboard::PageUp))
			letter.scaleCam(0.05);
		if(Keyboard::isKeyPressed(Keyboard::PageDown))
			letter.scaleCam(-0.05);

		float time= timer.getElapsedTime().asMilliseconds();
		time=time/800;
		timer.restart();

		system("cls");
		printf("TIME %5.2f\n",time);
		printf("%3i fps\n",(int)(1/time));

		letter.update(time);

		window.clear();

		letter.draw(&window);

		window.display();
	}
 
	return 0;
}