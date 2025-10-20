#pragma once
#include "main.h"

class CPlayer
{
	Vector2f coords;
	Vector2f motion;
	float dSize;
	float radius;
	float vTimer;
	int lives;
	int score;
	Texture pTexture;
	Sprite pSprite;
public:
	void update(RenderWindow *wind,CGameMap *i_map,float time);
	void checkCollusion(CGameMap *i_map);
	void draw(RenderWindow *wind,CGameMap *i_map);
	void eatObj(float i_size);
	Vector2f getPosition();
	float getRadius();
	int getLives();
	int getScore();
	void loadData();
	void reset();
	CPlayer(void);
	~CPlayer(void);
};

class CGameMap
{
	struct mapObjectNode
	{
		Vector2f pos;
		Vector2f dpos;
		float size;
		float dSize;
		float rotation;
		Color color;
		bool good;
		bool alive;
	};
	struct findPred
	{
		bool operator() (mapObjectNode i)
		{
			return (pow(pow(i.pos.x-pos.x,2)+pow(i.pos.y-pos.y,2),1./2.)<=radius)&&(i.size<radius);
		}
		Vector2f pos;
		float radius;
	}findCond;
	Vector2i mapSize;
	Vector2f offset;
	Vector2f cOffset;
	float mScale;
	int maxAmOfObj;
	int amOfGood,amOfBad;
	int level;
	vector<mapObjectNode> obj;
	Texture goodT,badT;
	Sprite goodS,badS;
	Texture sandTexture;
	Sprite background;
public:
	void update(Vector2u i_windSize,CPlayer *devourer,float i_time);
	void draw(RenderWindow *wind);
	void drawMarker(RenderWindow *wind);
	void moveObj(CPlayer *devourer,float i_time);
	void countOffset(Vector2u i_windSize,Vector2f PlayerCoords,float i_time);
	void countScale(Vector2u i_windSize,float devourerRadius);
	void CheckCollision(Vector2f coords,float i_radius,Vector2f &i_motion);
	void CGameMap::CheckCollision(Vector2f i_pos,float i_radius,Vector2f &i_motion,mapObjectNode &i_obj);
	bool CheckDamage(Vector2f coords,float i_radius);
	Vector2f getOffset();
	Vector2i getMapSize();
	float getScale();
	bool getMinSide(Vector2u i_windSize);
	int getLevel();
	void setMapSize(Vector2i i_size);
	void addObj(Vector2f i_pos,float i_size,Color i_color,bool i_good);
	void autoFillObj(CPlayer *);
	void eatObj(Vector2f i_pos,float i_radius,CPlayer *devourer);
	void eatAllObj(bool good);
	void levelUp();
	void reset();
	CGameMap(void);
	~CGameMap(void);
};


