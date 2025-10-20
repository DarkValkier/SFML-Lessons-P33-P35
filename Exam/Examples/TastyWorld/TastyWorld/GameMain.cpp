#include "GameMain.h"


void CGameMain::update(RenderWindow *wind,float time)
{
	background.setTextureRect(IntRect((bTexture.getSize().x-wind->getSize().x)/2,(bTexture.getSize().y-wind->getSize().y)/2,wind->getSize().x,wind->getSize().y));
	//background.setTextureRect(IntRect(10,10,10,10));
	wind->draw(background);
	switch(gState)
	{
	case MainMenu:
		{
			switch(ButtonList.getClick())
			{
			case 0:
				{
					ButtonList.removeAllButtons();
					loadInterface(Game);
					gState=Game;
					gMap.setMapSize(Vector2i(3200,2400));
					break;
				}
			case 1:
				ButtonList.removeAllButtons();
				loadInterface(Settings);
				gState=Settings;
				break;
			case 2:
				wind->close();
				break;
			}
			break;
		}
	case Game:
		{
						
			gMap.update(wind->getSize(),&p,time);
			p.update(wind,&gMap,time);
			
			if(Keyboard::isKeyPressed(Keyboard::Escape))
			{
				ButtonList.removeAllButtons();
				loadInterface(Pause);
				gState=Pause;
			}
			gMap.draw(wind);
			p.draw(wind,&gMap);
			CTitle::drawVignette(wind,time);
			CTitle::drawText(Vector2f(130,30),L"Уровень "+to_string(gMap.getLevel()),wind);
			CTitle::drawText(Vector2f(400,30),to_string(p.getScore()),wind);
			CTitle::drawText(Vector2f(670,30),L"Жизней: "+to_string(p.getLives()),wind);
			if(p.getLives()<=0)
			{
				ButtonList.removeAllButtons();
				EGTimer=1;
				CTitle::setVignette(Color(0,0,0,255));
				gState=GameEnd;
			}
			break;
		}
	case GameEnd:
		{
			gMap.draw(wind);
			p.draw(wind,&gMap);
			CTitle::drawVignette(wind,time);
			CTitle::drawText(Vector2f(130,30),L"Уровень "+to_string(gMap.getLevel()),wind);
			CTitle::drawText(Vector2f(670,30),L"Жизней: "+to_string(p.getLives()),wind);
			if(EGTimer>0)
			{
				EGTimer-=time;
				if(EGTimer<=0)
				{
					EGTimer=0;
					loadInterface(GameEnd);
				}
			}
			if(EGTimer==0)
			{
				CTitle::drawText(Vector2f(400,200),L"Ваш счет",wind);
				CTitle::drawText(Vector2f(400,250),to_string(p.getScore()),wind);
				switch(ButtonList.getClick())
				{
				case 0:
					ButtonList.removeAllButtons();
					p.reset();
					gMap.reset();
					loadInterface(MainMenu);
					gState=MainMenu;
					break;
				}
			}
			break;
		}
	case OutPause:
		{
			CTitle::drawText(Vector2f(400,200),L"Вы хотите выйти?",wind);
			switch(ButtonList.getClick())
			{
			case 0:
				ButtonList.removeAllButtons();
				loadInterface(Pause);
				gState=Pause;
				break;
			case 1:
				ButtonList.removeAllButtons();
				p.reset();
				gMap.reset();
				loadInterface(MainMenu);
				gState=MainMenu;
				break;
			}
			break;
		}
	case Pause:
		{
			switch(ButtonList.getClick())
			{
			case 0:
				{
					ButtonList.removeAllButtons();
					loadInterface(Game);
					gState=Game;
					break;
				}
			case 2:
				ButtonList.removeAllButtons();
				loadInterface(OutPause);
				gState=OutPause;
				break;
			}
			break;
		}
	case Settings:
		switch(ButtonList.getClick())
		{
		case 0:
				ButtonList.removeAllButtons();
				loadInterface(MainMenu);
				gState=MainMenu;
				break;
		case 1:
			setFullScreen(!getFullScreen());
			ButtonList.removeAllButtons();
			loadInterface(Settings);
			break;
		}
		break;
	default:
		gState=MainMenu;
	}
	ButtonList.update(wind);
	ButtonList.draw(wind);
	LvlBtnList.update(wind);
	LvlBtnList.draw(wind);
}

void CGameMain::loadInterface(gameStatus i_state)
{
	switch(i_state)
	{
	case MainMenu:
		ButtonList.addButton(FloatRect(0,-88,300,75),CButtons::btnAlignX::centerX,CButtons::btnAlignY::centerY,L"Игра",0,true);
		ButtonList.addButton(FloatRect(0,0,300,75),CButtons::btnAlignX::centerX,CButtons::btnAlignY::centerY,L"Настройки",1,true);
		ButtonList.addButton(FloatRect(0,188,200,75),CButtons::btnAlignX::centerX,CButtons::btnAlignY::centerY,L"Выход",2,true);
		break;
	case Game:
		//ButtonList.addButton(FloatRect(0,0,300,75),CButtons::btnAlignX::right,CButtons::btnAlignY::bottom,L"Назад",0,true);
		break;
	case GameEnd:
		ButtonList.addButton(FloatRect(0,88,300,75),CButtons::btnAlignX::centerX,CButtons::btnAlignY::centerY,L"На главную",0,true);
		break;
	case OutPause:
		ButtonList.addButton(FloatRect(-100,88,150,75),CButtons::btnAlignX::centerX,CButtons::btnAlignY::centerY,L"Да",1,true);
		ButtonList.addButton(FloatRect(100,88,150,75),CButtons::btnAlignX::centerX,CButtons::btnAlignY::centerY,L"Нет",0,true);
		break;
	case Pause:
		ButtonList.addButton(FloatRect(0,-88,300,75),CButtons::btnAlignX::centerX,CButtons::btnAlignY::centerY,L"Продолжить",0,true);
		ButtonList.addButton(FloatRect(0,0,300,75),CButtons::btnAlignX::centerX,CButtons::btnAlignY::centerY,L"Настройки",1,false);
		ButtonList.addButton(FloatRect(0,188,300,75),CButtons::btnAlignX::centerX,CButtons::btnAlignY::centerY,L"Гл. меню",2,true);
		break;
	case Settings:
		ButtonList.addButton(FloatRect(0,0,300,75),CButtons::btnAlignX::right,CButtons::btnAlignY::bottom,L"Назад",0,true);
		if(getFullScreen())
			ButtonList.addButton(FloatRect(0,50,600,75),CButtons::btnAlignX::centerX,CButtons::btnAlignY::top,L"Оконный режим",1,true);
		else
			ButtonList.addButton(FloatRect(0,50,600,75),CButtons::btnAlignX::centerX,CButtons::btnAlignY::top,L"Полный экран",1,true);
		break;
	}
}

void CGameMain::loadData()
{
	bTexture.loadFromFile("Data/Textures/Interface/background.jpg");
	background.setTexture(bTexture);
}

CGameMain::CGameMain(void):gState(MainMenu),EGTimer(0)
{ 
	// === Начальная запись в лог ===
	ofstream logFile;
	logFile.open(logFileWay,ios_base::out);
	logFile<<"Game started!"<<endl<<"Tasty World v1.0 2016"<<endl<<" ===== GAME WORK START ====="<<endl;
	logFile.close();
	loadData();
	loadInterface(MainMenu);
}



CGameMain::~CGameMain(void)
{
	ofstream logFile;
	logFile.open(logFileWay,ios_base::app);
	logFile<<" ===== GAME WORK END ====="<<endl<<"Game has finished it`s work!"<<endl;
	logFile.close();
}

