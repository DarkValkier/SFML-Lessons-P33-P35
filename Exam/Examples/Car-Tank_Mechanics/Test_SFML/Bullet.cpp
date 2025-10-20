#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void CBullet::update(float time)
{
	bul *work=head;
	while(work!=NULL)
	{
		float yBuf=-(cos(work->angle*3.14159/180)*work->speed);
		float xBuf=cos((fabs(work->angle-90))*3.14159/180)*work->speed;
		if((CTMap::checkCollision(work->x+xBuf*time,work->y))||(CTMap::checkCollision(work->x,work->y+yBuf*time)))
			work->alive=false;
		else
		{
			work->y+=yBuf*time;
			work->x+=xBuf*time;
			work->clock-=time;
		}
		//if((work->x>550)||(work->x<-100)||(work->y>550)||(work->y<-100))
		//if((work->clock<=0)||((work->x>wind->getSize().x)||(work->x<0)||(work->y>wind->getSize().y)||(work->y<0)))
		work=work->next;
	}
	clearNodeBullet();
	displayNodeBullet();
}

void CBullet::createBullet(int iType,float iX,float iY,float iAngle,float iSpeed)
{
	//if(head==NULL)
	//{
		bul *work=new bul;
		work->x=iX;
		work->y=iY;
		if(iType==3)
			work->angle=iAngle-22.5+rand() % 45;
		else
			work->angle=iAngle;
		work->speed=iSpeed;
		work->alive=true;
		work->clock=1;
		work->type=iType;
		if(head==NULL)
		{
			work->next=head;
			head=work;
			//cout<<" ----- Bullet created -----"<<endl;
			return;
		}
		bul *last=head;
		while(last->next!=NULL)
			last=last->next;
		work->next=NULL;
		last->next=work;
		//cout<<" ----- Bullet created -----"<<endl;
	//}
}

void CBullet::displayNodeBullet()
{
	bul *work=head;
	while(work!=NULL)
	{
		RectangleShape bullet;
		bullet.setFillColor(Color::White);
		/*if(work->type==0)
			bullet.setFillColor(Color::Red);*/
		bullet.setSize(Vector2f(10,10));
		bullet.setOrigin(5,5);
		bullet.setPosition(work->x-CTMap::getOffset().x,work->y-CTMap::getOffset().y);
		bullet.setRotation(work->angle);
		wind->draw(bullet);
		work=work->next;
	}
}

void CBullet::clearNodeBullet()
{
	bul *work=head;
	bul *perv=NULL;
	while(work!=NULL)
	{
		if(!work->alive)
		{
			switch (work->type)
			{
			case 1:
				{
					for(int i=0;i<6;i++)
						createBullet(0,work->x,work->y,work->angle+30+60*i,work->speed);
					//system("pause");
					break;
				}
			case 2:
				{
					for(int i=0;i<6;i++)
						createBullet(1,work->x,work->y,work->angle+30+60*i,work->speed);
					//system("pause");
					break;
				}
			}
			if(perv==NULL)
			{
				perv=work;
				work=work->next;
				delete perv;
				perv=NULL;
				head=work;
			}
			else
			{
				perv->next=work->next;
				delete work;
				work=perv->next;
			}
			//cout<<endl<<" ----- Bullet destroyed -----"<<endl<<endl;
		}
		else
		{
			perv=work;
			work=work->next;
		}
	}
}
void CBullet::deleteNodeBullet()
{
	while(head!=NULL)
	{
		bul *work=head;
		head=head->next;
		delete work;
	}
}

CBullet::CBullet()
{
}

/*Sprite CBullet::getSprite()
{
	Sprite ret;
	ret.setPosition(x,y);
	ret.setRotation(angle);
	ret.setColor(Color::White);
	return ret;
}*/

CBullet::~CBullet(void)
{
}
