#include "TMap.h"
#include <iostream>

CTMap::CTMap()
{
}


CTMap::~CTMap(void)
{
}

void CTMap::draw(float ofX,float ofY)
{
	offsetX=ofX;
	offsetY=ofY;
	if(Keyboard::isKeyPressed(Keyboard::M))
		{
			for(int i=0;i<height;i++)
			{
				for(int j=0;j<width;j++)
					printf("%1c",TileMap[i][j]);
				std::cout<<std::endl;
			}
			system("pause");
		}
	RectangleShape rect;
	rect.setSize(Vector2f(64,64));
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{
			rect.setPosition(j*64-ofX,i*64-ofY);
			switch(TileMap[i][j])
			{
			case 'B':
				{
					rect.setFillColor(Color::Red);
					break;
				}
			case '1':
				{
					rect.setFillColor(Color::Cyan);
					break;
				}
			default:
				{
					rect.setFillColor(Color::Cyan);
					break;
				}
			}
			wind->draw(rect);			
		}
	
}

Vector2f CTMap::getOffset()
{
	return Vector2f(offsetX,offsetY);
}

int CTMap::checkCollision(float x,float y)
{
	if(TileMap[int(y/64)][int(x/64)]=='B')
		return 1;
	return 0;
}
