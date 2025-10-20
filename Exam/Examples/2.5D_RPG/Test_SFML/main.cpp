/*#include <SFML/Graphics.hpp>
#define _WIN32_WINNT 0x0500
#include <Windows.h>*/
 
//int main()
//{
//	HWND hWnd = GetConsoleWindow();//берем текущ консоль, (скрывает консоль (работает только под windows))
//	ShowWindow(hWnd, SW_HIDE);//скрывает консоль
//	return 0;
//}

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>

using namespace std; 
using namespace sf;

float offsetX=0,offsetY=0;
int wind_active=1,console_active=0;

const int H=24;
const int W=30;
const int WindowHeight=20;
const int WindowWidth=30;

String TileMap[H] = {
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"B6111111111111BB1111111111111B",
	"B             BB    P        B",
	"B     P       BB             B",
	"B    23332    11    23332    B",
	"B    45554          45554    B",
	"B    45554          45554    B",
	"B    45554    BB    45554    B",
	"B    23332    BB    23332    B",
	"B             BB  P      P   B",
	"B            B11B            B",
	"B           B1551B           B",
	"BBBBBB   BBB155551BBB   BBBBBB",
	"B11111   111B5555B111   11111B",
	"B           1B55B1P          B",
	"B     P      1BB1            B",
	"B    23332    11    23332 P  B",
	"B    45554 P     P  45554    B",
	"B    45554          45554    B",
	"B    45554    BB    45554  P B",
	"B   P23332   B11B   23332    B",
	"B           B1  1B           B",
	"BBBBBBBBBBBB1    1BBBBBBBBBBBB",
	"111111111111      111111111111",
	/*"BBBBBBBBBBBBBBBB              ",
	"B6111111111111BB              ",
	"B             BB              ",
	"B     P       BB              ",
	"B    23332    BB              ",
	"B    45554    BB              ",
	"B    45554    BB              ",
	"B    45554    BB              ",
	"B    23332    BB              ",
	"B             BB              ",
	"B            B11B             ",
	"B           B1551B            ",
	"BBBBBB   BBB155551BBBBBBBBBBBB",
	"B11111   111B5555B11111111111B",
	"B           1B55B1P          B",
	"B     P      1BB1            B",
	"B    23332    11    23332 P  B",
	"B    45554 P     P  45554    B",
	"B    45554          45554    B",
	"B    45554    BB    45554  P B",
	"B   P23332   B11B   23332    B",
	"B           B1  1B           B",
	"BBBBBBBBBBBB1    1BBBBBBBBBBBB",
	"111111111111      111111111111",*/

};

RenderWindow window(VideoMode(WindowWidth*32,WindowHeight*32),"Game window",sf::Style::Close);

class CPLAYER
{
public:
	float dx,dy;
	FloatRect rect;
	Texture texture;
	Sprite sprite;
	float curFrame;
	int dir;
	int r,g,b;
	CPLAYER::CPLAYER(Texture &image)
	{
		sprite.setTexture(image);
		rect=FloatRect(32,32,32,48);
		curFrame=0;
		dir=0;
		sprite.setTextureRect(IntRect(32*int(curFrame)+32,48*dir,32,48));
		float x,y;
		if((rect.left>(WindowWidth*32)/2)&&(rect.left<(W*32)-(WindowWidth*32)/2)) 
		{
			offsetX=rect.left-(WindowWidth*32)/2;
			x=(WindowWidth*32)/2;
		}
		else
			x=rect.left;
		if((rect.top>(WindowHeight*32)/2)&&(rect.top<(H*32)-(WindowHeight*32)/2)) 
		{
			offsetY=rect.top-(WindowHeight*32)/2;
			y=(WindowHeight*32)/2;
		}
		else
			y=rect.top;
		sprite.setPosition(x,y);
		dx=dy=0;
		r=g=b=255;
	}
	void update(float time)
	{
		if(wind_active)
			keyboardCheck();
		// Движение персонажа
		rect.left+=dx*time;
		Collision('x');
		rect.top+=dy*time;
		Collision('y');

		if((dx!=0)||(dy!=0))
		{
			curFrame+=0.005*time;
			if(curFrame > 3) curFrame-=3;
			sprite.setTextureRect(IntRect(32*int(curFrame)+32,48*dir,32,48));
			sprite.setPosition(rect.left-offsetX,rect.top-offsetY);
			dx=0;
			dy=0;
		}
		/*if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))&&(wind_active))
		{
			if(r>0) r=g=b=r-1;
			sprite.setColor(sf::Color::Color(r,g,b,255));
			cout<<"r="<<r;
		}
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Right))&&(wind_active))
		{
			if(r<255) r=g=b=r+1;
			sprite.setColor(sf::Color::Color(r,g,b,255));
			cout<<"r="<<r;
		}*/
	}
	void Collision(char f)
	{
		for(int i=rect.top/32;i<(rect.top+rect.height)/32;i++)
			for(int j=rect.left/32;j<(rect.left+rect.width)/32;j++)
			{
				if(TileMap[i][j]=='B')
				{
					//cout<<"a";
					if((dx>0)&&(f=='x')) rect.left= j*32 - rect.width;
					if((dx<0)&&(f=='x')) rect.left= j*32 + 32;
					if((dir==0)&&(f=='y')) rect.top= i*32 - rect.height;
					if((dir==3)&&(f=='y')) rect.top= i*32 + 32;
				}
				if(TileMap[i][j]=='P')
				{
					TileMap[i][j]=' ';
				}
			}
	}
	void keyboardCheck()
	{
		// Проверка клавиш
		if(Keyboard::isKeyPressed(Keyboard::Left))
		{
			dir=1;
			dx=-0.1;
		}
		if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			if(Keyboard::isKeyPressed(Keyboard::Left))
			{
				dx=0;
			}
			else
			{
				dir=2;
				dx=0.1;
			}
		}
		if(Keyboard::isKeyPressed(Keyboard::Up))
		{
			dir=3;
			dy=-0.1;
		}
		if(Keyboard::isKeyPressed(Keyboard::Down))
		{
			if(Keyboard::isKeyPressed(Keyboard::Up))
			{
				dy=0;
			}
			else
			{
				dir=0;
				dy=0.1;
			}
		}
		if((dx!=0)&&(dy!=0))
		{
			dx=dx-dx/4;
			dy=dy-dy/4;
		}
	}
};

class CNPC
{
public:
	float dx,dy;
	FloatRect rect;
	Texture texture;
	Sprite sprite;
	float curFrame;
	int dir;
	int r,g,b;
	float mX,mY;
	CNPC::CNPC(Texture &image)
	{
		sprite.setTexture(image);
		mX=0;mY=0;
		rect=FloatRect(150,150,32,32);
		curFrame=0;
		dir=0;
		sprite.setTextureRect(IntRect(32*int(curFrame)+32,32*dir+192,32,32));
		float x,y;
		x=rect.left;
		y=rect.top;
		sprite.setPosition(x-offsetX,y-offsetY);
		dx=dy=0;
		r=g=b=255;
	}
	void update(float time)
	{
		/*if(wind_active)
			keyboardCheck();*/
		if(!((mX<1)&&(mX>-1)))
			moveX();
		if(!((mY<1)&&(mY>-1)))
			moveY();
		if((dx!=0)&&(dy!=0))
		{
			dx=dx-dx/4;
			dy=dy-dy/4;
		}
		// Движение персонажа
		rect.left+=dx*time;
		mX-=dx*time;
		Collision('x');
		rect.top+=dy*time;
		mY-=dy*time;
		Collision('y');
		if(Keyboard::isKeyPressed(Keyboard::F10))
			cout<<endl<<"mX:"<<mX<<endl<<"mY:"<<mY;
		if((dx!=0)||(dy!=0))
		{
			curFrame+=0.005*time;
			if(curFrame > 2) curFrame-=2;
			dx=0;
			dy=0;
		}
		sprite.setTextureRect(IntRect(32*int(curFrame)+32,32*dir+128,32,32));
		sprite.setPosition(rect.left-offsetX,rect.top-offsetY);
		/*if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))&&(wind_active))
		{
			if(r>0) r=g=b=r-1;
			sprite.setColor(sf::Color::Color(r,g,b,255));
			cout<<"r="<<r;
		}
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Right))&&(wind_active))
		{
			if(r<255) r=g=b=r+1;
			sprite.setColor(sf::Color::Color(r,g,b,255));
			cout<<"r="<<r;
		}*/
	}
	void Collision(char f)
	{
		for(int i=rect.top/32;i<(rect.top+rect.height)/32;i++)
			for(int j=rect.left/32;j<(rect.left+rect.width)/32;j++)
			{
				if(TileMap[i][j]=='B')
				{
					//cout<<"a";
					if((dx>0)&&(f=='x')) rect.left= j*32 - rect.width;
					if((dx<0)&&(f=='x')) rect.left= j*32 + 32;
					if((dir==0)&&(f=='y')) rect.top= i*32 - rect.height;
					if((dir==3)&&(f=='y')) rect.top= i*32 + 32;
				}
				if(TileMap[i][j]=='P')
				{
					TileMap[i][j]=' ';
				}
			}
			
	}
	void moveXY(int x,int y)
	{
		mX=x-rect.left;
		mY=y-rect.top;
	}
	void moveX()
	{
		// Проверка клавиш
		if(mX<0)
		{
			dir=1;
			dx=-0.1;
		}
		if(mX>0)
		{
			dir=2;
			dx=0.1;
		}
		
	}
	void moveY()
	{
		// Проверка клавиш
		if(mY<0)
		{
			dir=3;
			dy=-0.1;
		}
		if(mY>0)
		{
			dir=0;
			dy=0.1;
		}
	}
};

int duration(int x1,int y1,int x2,int y2)
{
	/*int x,y;
	x=x2-x1;
	y=y2-y2;
	int ret_dur=pow(pow(x,2)+pow(y,2),1/2);*/
	int ret_dur=abs(abs(x1-x2) + abs(y1-y2));
	return ret_dur;
}

char check_key(char l_char)
{
	char ret='\0';
	int shift=0;
	if((Keyboard::isKeyPressed(Keyboard::LShift))||(Keyboard::isKeyPressed(Keyboard::RShift)))
		shift=1;
	if(Keyboard::isKeyPressed(Keyboard::BackSpace))
		return '\b';
	if(Keyboard::isKeyPressed(Keyboard::Space))
		return ' ';
	//int i=0;
	for(int i=0;i<36;i++)
	{
		if(Keyboard::isKeyPressed(Keyboard::Key(i)))
		{
			
			if((i>=0)&&(i<=25))
			{
				if(shift)
					ret=65+i;
				else
					ret='a'+i;
			}
			if((i>=26)&&(i<=35))
			{
				ret='0'+(i-26);
			}
		}
	}
	if(ret!=l_char)
		cout<<"ret:"<<ret<<endl;
	return ret;
}

void console(Font font)
{
	wind_active=0;
	cout<<"Console on!"<<endl;
	int console_work=1,theS=0;
	char l_char='\0',w_char='\0';
	char command[49]={'\0'};
	int e_symb=0;
	RectangleShape cons_window(Vector2f(WindowWidth*32,(WindowHeight*32)/4));
	cons_window.setPosition(0,3*((WindowHeight*32)/4));
	cons_window.setFillColor(Color::Color(0,0,0,127));
	Text txt ;
    txt.setPosition ( 50 , 50 ) ;
	txt.setString ( L"Hello VVorld!" ) ;
    txt.setFont ( font ) ;
	txt.setCharacterSize(64);
	txt.setColor(sf::Color::White);
	txt.setStyle(sf::Text::Regular);
	txt.setString ( L"Command:" ) ;
	txt.setPosition (0,3*((WindowHeight*32)/4)+2);
	txt.setCharacterSize(14);
	//window.draw(txt);
	while(console_work)
	{
		w_char=check_key(l_char);
		if((w_char=='\0')||(w_char!=l_char))
			theS=0;
		else
			//if(w_char==l_char)
			theS=1;
		l_char=w_char;
		if((!theS)&&(w_char!='\0'))
		{
			if((e_symb>0)&&(w_char=='\b'))
			{
				command[--e_symb]='\0';
				cout<<"command:"<<command<<endl;
			}
			else
			{
				if(e_symb<48)
				{
					command[e_symb]=l_char;
					command[++e_symb]='\0';
					cout<<"command:"<<command<<endl;
				}
			}

		}
		txt.setString ( command ) ;
		if(Keyboard::isKeyPressed(Keyboard::Tilde))
			console_work=0;

		window.draw(cons_window);
		window.draw(txt);
		window.display();
	}
	//gets(command);
	/*if(strstr(command,"moveNPC"))
	{
	int x,y;
	cout<<"X:";
	cin>>x;
	cout<<"Y:";
	cin>>y;
	npc.moveXY(x,y);
	}*/
	//system("pause>NUL");
	cout<<"Console off!"<<endl;
	wind_active=1;
}

void main()
{
	Texture t;
	t.loadFromFile("Lancer02.png");
	Texture t_npc;
	t_npc.loadFromFile("actor110.png");
	Texture tileSet;
	tileSet.loadFromFile("scrap4.png");
	Sprite tile(tileSet);

	Font font;
	font.loadFromFile("Dynar-Medium.ttf");

	

	/*Sprite s;
	float curFrame=0;
	int dir=0;
	s.setTexture(t);
	s.setTextureRect(IntRect(0,0,32,48));
	s.setPosition(50,100);
	*/
	CPLAYER p(t);
	CNPC npc(t_npc);
	Clock clock;

	RectangleShape rectangle;
	npc.moveXY(100,170);
	while(window.isOpen())
	{
		float time= clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time=time/800;
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window.close();
			if(event.type == sf::Event::GainedFocus)
			{
				wind_active=1;
				cout<<"wind_active set to 1\n";
			}
			if(event.type == sf::Event::LostFocus)
			{
				wind_active=0;
				cout<<"wind_active set to 0\n";
			}
			// CONSOLE
			if(Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}

		}
		if(console_active)
		{
			console(font);
			console_active=0;
		}
		if(time>100)
			continue;
		window.clear(Color::Blue);
		for(int i=0;i<H;i++)
			for(int j=0;j<W;j++)
			{
				if(TileMap[i][j]=='B') tile.setTextureRect( IntRect(16,16,32,32) );
				if(TileMap[i][j]=='P') tile.setTextureRect( IntRect(112,208,32,32) );
				if(TileMap[i][j]=='1') tile.setTextureRect( IntRect(400,48,32,32) );
				if(TileMap[i][j]=='2') tile.setTextureRect( IntRect(112,16,32,32) );
				if(TileMap[i][j]=='3') tile.setTextureRect( IntRect(80,16,32,32) );
				if(TileMap[i][j]=='4') tile.setTextureRect( IntRect(112,48,32,32) );
				if(TileMap[i][j]=='5') tile.setTextureRect( IntRect(144,16,32,32) );
				if(TileMap[i][j]=='6') tile.setTextureRect( IntRect(208,16,32,32) );
				if(TileMap[i][j]==' ') tile.setTextureRect( IntRect(80,48,32,32) );
				//rectangle.setScale(32,32);
				/*int R=7;
				if(duration(j,i,int((p.rect.left+16)/32),int((p.rect.top+48)/32))<R)
				{
					//int c=duration(j,i,p.rect.left/32,p.rect.top/32)/4;
					//tile.setColor(Color::White);
					int c=duration(j,i,int((p.rect.left+16)/32),int((p.rect.top+48)/32))*(192/R);
					tile.setColor(Color::Color(225-c,225-c,225-c,225));
				}
				else
					tile.setColor(Color::Color(63,63,63,225));*/
				tile.setPosition(j*32-offsetX,i*32-offsetY);
				window.draw(tile);
			}
		/*RectangleShape rectangle(Vector2f(8,8));
		for(int i=0;i<WindowHeight*4;i++)
			for(int j=0;j<WindowWidth*4;j++)
			{
				rectangle.setFillColor(Color::Red);
				rectangle.setPosition(j*8,i*8);
				window.draw(rectangle);
			}*/
		/*system("cls");
		cout<<p.rect.left/32;*/
		p.update(time);
		npc.moveXY(p.rect.left+0,p.rect.top-64);
		npc.update(time);
		if((p.rect.left>(WindowWidth*32)/2)&&(p.rect.left<(W*32)-(WindowWidth*32)/2)) offsetX=p.rect.left-(WindowWidth*32)/2;
		if((p.rect.top>(WindowHeight*32)/2)&&(p.rect.top<(H*32)-(WindowHeight*32)/2)) offsetY=p.rect.top-(WindowHeight*32)/2;
		window.draw(npc.sprite);
		window.draw(p.sprite);
		window.display();
	}
}






