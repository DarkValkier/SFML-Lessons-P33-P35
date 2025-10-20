#pragma once
#include "main.h"
#include "Buttons.h"
#include "SLButtons.h"
#include "PlayerMap.h"

enum gameStatus
	{
		MainMenu,
		SelectLevel,
		Game,
		GameEnd,
		OutPause,
		Pause,
		Settings
	};

class CGameMain
{
	gameStatus gState;
	CButtons ButtonList;
	SLButtons LvlBtnList;
	CGameMap gMap;
	CPlayer p;
	Texture bTexture;
	Sprite background;
	float EGTimer;

public:
	void update(RenderWindow *,float);
	void loadInterface(gameStatus i_state);
	void loadData();
	CGameMain(void);
	~CGameMain(void);
};

