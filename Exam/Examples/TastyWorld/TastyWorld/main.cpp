#include "main.h"
#include "GameMain.h"

Font CTitle::tFont = Font();
Text CTitle::tTitle = Text();
Color CTitle::tColor = Color();
Color CTitle::vColor = Color();
Color CTitle::vDColor = Color();
VertexArray CTitle::a = VertexArray();

unsigned int windowWidth=800;
unsigned int windowHeight=600;

bool isFullScreen[2]={false,false};

void setFullScreen(bool i)
{
	isFullScreen[0]=i;
}

bool getFullScreen()
{
	return isFullScreen[0];
}

/* == ����� ��������� � ��� (�������� ������, ����������� ��������� � ���� ���������) == */
void sendToLog(const char i_module[32],string i_message)
{
	ofstream logFile;
	logFile.open(logFileWay,ios_base::app);
	logFile<<" "<<i_module<<" > "<<i_message<<endl;
	logFile.close();
}

int main()
{
	// === �������� �������� ������� ���� ===
	CGameMain gameObj;
	// === ���� ���� ===
	RenderWindow window(VideoMode(windowWidth,windowHeight),"Tasty World v1.0",Style::Close);
	Clock gameTimer;// ������
	CTitle::loadData();

	/*sf::VertexArray a(sf::Quads,4);

	a[0].color=Color::Red;
	a[1].color=Color::Red;
	a[2].color=Color::Color(0,0,0,0);
	a[3].color=Color::Red;*/

	// === ���������� ��� �������� FPS ===
	float fps_sec=0;
	int fps_frames=0;
	int fps=0;
	bool wind_active=true;
	while(window.isOpen())
	{
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window.close();
			if(event.type == sf::Event::GainedFocus)
			{
				wind_active=true;
				ostringstream mes;
				mes<<"The window has been gained focus!";
				sendToLog("main.cpp",mes.str());
			}
			if(event.type == sf::Event::LostFocus)
			{
				wind_active=false;
				ostringstream mes;
				mes<<"The window has been losted focus!";
				sendToLog("main.cpp",mes.str());
			}
		}
		// === ������ �������� ������� ===
		float time= gameTimer.getElapsedTime().asMilliseconds();
		time=time/800;
		gameTimer.restart();
		// === ����� � ������� ��������� � ������� ������� �������� ===
		if(time > 0.5)
		{
			ostringstream mes;
			mes<<"Too long delay ("<<time<<" ms)";
			sendToLog("main.cpp",mes.str());
		}
		if(isFullScreen[0]!=isFullScreen[1])
		{
			window.close();
			isFullScreen[1]=isFullScreen[0];
			if(isFullScreen[1])
				window.create(VideoMode(windowWidth,windowHeight),"Tasty World v1.0",Style::Fullscreen);
			else
				window.create(VideoMode(windowWidth,windowHeight),"Tasty World v1.0",Style::Close);
		}
		// === ������� �������� � ������ ������������ ���� ���� ������� ������� �������� ===
		if((!wind_active)||(time>0.5))
			continue;
		// === ������� FPS ===
		fps_sec+=time;
		fps_frames++;
		if(fps_sec>=0.25)
		{
			fps=4*fps_frames;
			fps_frames=0;
			fps_sec=0;
		}
		// === ����� �� ����� �������� � FPS ===
		system("cls");
		printf("Window size: %5i,%5i\n",window.getSize().x,window.getSize().y);
		printf("Time = %5.3f\nFPS = %3i\n",time,fps);
		// === ������� ������ ===
		window.clear();
		// === �������� ���������� �������� ������ ���� ===
		gameObj.update(&window,time);

		// === ����� �������� �� ����� ==
		window.display();
	}
	return 0;
}