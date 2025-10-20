#include "PlayerMap.h"

RenderWindow *rw;

void CPlayer::update(RenderWindow *wind,CGameMap *i_map,float i_time)
{
	rw=wind;
	float i_mapScale=i_map->getScale();
	Vector2f i_mapOffset=i_map->getOffset();
	// === Установка новых координат игрока ===
	Vector2f vcoords;
	vcoords.x=((Mouse::getPosition(*wind).x+i_mapOffset.x)-coords.x*i_mapScale);
	vcoords.y=((Mouse::getPosition(*wind).y+i_mapOffset.y)-coords.y*i_mapScale);
	motion=vcoords*(i_time/i_mapScale*2);
	//motion.y=vcoords.y*i_time/i_mapScale;
	// === Проверка на столкновения ===
	checkCollusion(i_map);
	coords+=motion;
	if(i_map->CheckDamage(coords,radius))
	{
		i_map->eatAllObj(false);
		lives--;
		CTitle::setVignette(Color(255,0,0,255));
		vTimer=2;
	}
	if(vTimer>0)
	{
		vTimer-=i_time;
		if(vTimer<=0)
		{
			vTimer=0;
			CTitle::setVignette(Color(0,0,0,0));
			//CTitle::resetVignette();
		}
	}
	cout<<" vTimer: "<<vTimer<<endl;
	// === Высчитывание и установка угла поворота игрока ===
	if(vcoords.x>=0)
		pSprite.setRotation(acosf((-vcoords.y)/(pow(pow(vcoords.x,2)+pow(vcoords.y,2),1./2.)))*180/3.14);
	else
		pSprite.setRotation(360-acosf((-vcoords.y)/(pow(pow(vcoords.x,2)+pow(vcoords.y,2),1./2.)))*180/3.14);
	if(dSize>i_map->getMapSize().y/8)
	{
		dSize=50.f;
		i_map->levelUp();
		score+=75;
	}
	if(dSize<50.f)
		dSize=50.f;
	if(radius!=dSize)
		radius+=(dSize-radius) * i_time ;
	printf("Player: X=%5.2f; Y=%5.2f\n",coords.x,coords.y);
	printf("Radius=%5.2f  dSize=%5.2f\n",radius,dSize);
	i_map->countScale(wind->getSize(),radius);
	i_map->countOffset(wind->getSize(),coords,i_time);
}

void CPlayer::checkCollusion(CGameMap *i_map)
{
	// === Проверка столкновений с объектами ===
	i_map->CheckCollision(Vector2f(coords.x,coords.y),radius,motion);
	Vector2i mapSize=i_map->getMapSize();
	// === Проверка столкновений с краями карты ===
	// -- По оси X --
	if(coords.x+motion.x-radius<=0)
		motion.x=radius-coords.x;
	if(coords.x+motion.x+radius>=mapSize.x)
		motion.x=mapSize.x-radius-coords.x;
	// -- По оси Y --
	if(coords.y+motion.y-radius<=0)
		motion.y=radius-coords.y;
	if(coords.y+motion.y+radius>=mapSize.y)
		motion.y=mapSize.y-radius-coords.y;
	//cout<<"MOTION: ("<<motion.x<<";"<<motion.y<<") = ("<<i_map->CheckCollision(Vector2f(coords.x+motion.x,coords.y),radius)<<";"<<i_map->CheckCollision(Vector2f(coords.x,coords.y+motion.y),radius)<<")"<<endl;
}

void CPlayer::draw(RenderWindow *wind,CGameMap *i_map)
{
	float i_mapScale=i_map->getScale();
	Vector2f i_mapOffset=i_map->getOffset();
	pSprite.setOrigin(50,50);
	pSprite.setPosition(coords.x*i_mapScale-i_mapOffset.x,coords.y*i_mapScale-i_mapOffset.y);
	pSprite.setScale((radius/50)*i_mapScale,(radius/50)*i_mapScale);
	wind->draw(pSprite);
}

void CPlayer::eatObj(float i_size)
{
	dSize+=float(i_size*eatCoeffcient);
	score+=int(i_size*eatCoeffcient);
}

Vector2f CPlayer::getPosition()
{
	return coords;
}

float CPlayer::getRadius()
{
	return radius;
}

int CPlayer::getLives()
{
	return lives;
}

int CPlayer::getScore()
{
	return score;
}

void CPlayer::loadData()
{
	pTexture.loadFromFile("data/textures/devourer.png");
	pSprite.setTexture(pTexture);
}

void CPlayer::reset()
{
	coords=Vector2f(100.f,100.f);
	radius=50.f;
	dSize=50.f;
	lives=3;
	score=0;
}

CPlayer::CPlayer(void):coords(100.f,100.f),radius(1.f),dSize(25.f),lives(3),score(0)
{
	loadData();
}

CPlayer::~CPlayer(void)
{
}


// === MAP ===

void CGameMap::update(Vector2u i_windSize,CPlayer *devourer,float i_time)
{
	if((mapSize.x==0)||(mapSize.y==0))
		return;
	// === Уничтожение съеденых объектов ===
	eatObj(devourer->getPosition(),devourer->getRadius(),devourer);
	// === Дозаполнение объектами ===
	autoFillObj(devourer);
	cout<<" - INTO MOVE - "<<endl;
	moveObj(devourer,i_time);
}

void CGameMap::draw(RenderWindow *wind)
{
	RectangleShape mapRect;
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
		{
			mapRect.setFillColor(Color::Color(Uint8(i*25.5),0,Uint8(j*25.5),255));
			mapRect.setSize(Vector2f(float(mapSize.x/10),float(mapSize.y/10)));
			mapRect.setPosition((mapRect.getSize().x*i*mScale)-offset.x,(mapRect.getSize().y*j*mScale)-offset.y);
			mapRect.setScale(mScale,mScale);
			wind->draw(mapRect);
		}
	/*background.setScale((mapSize.x/4096)*mScale,(mapSize.y/2848)*mScale);
	background.setPosition(0,0);
	background.setTextureRect(IntRect(0,0,800,600));
	wind->draw(background);*/
	// === Вывод объектов ===
	Sprite objSprite;
	for(int i=0;i<obj.size();i++)
	{
		if(obj[i].good)
			objSprite=goodS;
		else
			objSprite=badS;
		objSprite.setOrigin(50,50);
		objSprite.setPosition(obj[i].pos.x*mScale-offset.x,obj[i].pos.y*mScale-offset.y);
		objSprite.setScale((obj[i].size/50)*mScale,(obj[i].size/50)*mScale);
		objSprite.setRotation(obj[i].rotation);
		wind->draw(objSprite);
	}
	drawMarker(wind);
}

void CGameMap::drawMarker(RenderWindow *wind)
{
	vector<mapObjectNode>::iterator it;
	RectangleShape markerRect;
	markerRect.setFillColor(Color::Red);
	markerRect.setSize(Vector2f(50,50));
	markerRect.setOrigin(25,25);
	markerRect.setRotation(45);
	Vector2f markerPos(0,0);
	Vector2f markOffset=offset/mScale;
	for(it=obj.begin();it<obj.end();it++)
	{
		float dRadius=pow(pow(markOffset.x+wind->getSize().x/mScale/2-it->pos.x,2)+pow(markOffset.y+wind->getSize().y/mScale/2-it->pos.y,2),1./2.);
		if(dRadius>radiusDetection)
			continue;
		if(it->good)
			markerRect.setFillColor(Color::Green);
		else
			markerRect.setFillColor(Color::Red);
		markerPos=Vector2f(0,0);
		
		if((it->pos.x>markOffset.x)&&(it->pos.x<(markOffset.x+wind->getSize().x/mScale)))
			markerPos.x=it->pos.x-markOffset.x;
		else
			if(it->pos.x>markOffset.x)
				markerPos.x+=wind->getSize().x/mScale;
		if((it->pos.y>markOffset.y)&&(it->pos.y<(markOffset.y+wind->getSize().y/mScale)))
			markerPos.y=it->pos.y-markOffset.y;
		else
			if(it->pos.y>markOffset.y)
				markerPos.y+=wind->getSize().y/mScale;
		if(pow(dRadius,2)>pow(wind->getSize().x/mScale/2,2)+pow(wind->getSize().y/mScale/2,2))
		{
			markerRect.setScale(1-(dRadius/radiusDetection),1-(dRadius/radiusDetection));
			markerRect.setPosition(markerPos*mScale);
			wind->draw(markerRect);
		}
	}
}

void CGameMap::moveObj(CPlayer *devourer,float i_time)
{
	vector<mapObjectNode>::iterator it;
	int k_n=0;
	for(it=obj.begin();it<obj.end();it++)
	{
		if(!it->alive)
			continue;
		if(it->good)
		{
			if(it->size<devourer->getRadius())
				k_n++;
			if((it->dSize<devourer->getRadius()-30)||(it->dSize>devourer->getRadius()+20))
				it->dSize=devourer->getRadius()-30+rand()%50;
		}
		if(!it->good&&((it->dSize<devourer->getRadius()-10)||(it->dSize>devourer->getRadius()+60)))
			it->dSize=devourer->getRadius()-10+rand()%40;
	}
	if(k_n==0)
		for(it=obj.begin();it<obj.end();it++)
			if(it->good&&it->alive)
				it->dSize=devourer->getRadius()-30+rand()%20;		
	findCond.pos=devourer->getPosition();
	findCond.radius=devourer->getRadius()*10;
	it=obj.begin();
	while((it=find_if(it,obj.end(),findCond))!=obj.end())
	{
		if(!it->alive)
		{
			it++;
			continue;
		}
		if(!it->good)
		{
			Vector2f motion;
			motion.x=(findCond.pos.x-it->pos.x)*i_time/1.5;
			motion.y=(findCond.pos.y-it->pos.y)*i_time/1.5;
			CheckCollision(it->pos,it->size,motion,*it);
			if(motion.x>=0)
				it->rotation=acosf((-motion.y)/(pow(pow(motion.x,2)+pow(motion.y,2),1./2.)))*180/3.14;
			else
				it->rotation=360-acosf((-motion.y)/(pow(pow(motion.x,2)+pow(motion.y,2),1./2.)))*180/3.14;
			it->pos+=motion;
		}
		//cout<<"("<<it->pos.x<<";"<<it->pos.y<<")";
		it++;
	}
	for(it=obj.begin();it<obj.end();it++)
		if(it->alive)
			it->size+=(it->dSize-it->size)*i_time;
		else
			it->size+=(it->dSize-it->size)*i_time*10;

	it=obj.begin();
	while(it!=obj.end())
	{
		if((!it->alive)&&(it->size<=10))
		{
			obj.erase(it);
			it=obj.begin();
		}
		it++;
	}

	struct Cond
	{
		bool operator() (mapObjectNode i)
		{ 
			return i.good;
		}
	} findPred;

	it=obj.begin();
	while((it=find_if(it,obj.end(),findPred))!=obj.end())
	{
		if(!it->alive)
		{
			it++;
			continue;
		}
		Vector2f motion;
		if((it->dpos.x-it->pos.x)>100)
			motion.x=100*i_time*(it->dpos.x-it->pos.x)/fabs(it->dpos.x-it->pos.x);
		else
			motion.x=(it->dpos.x-it->pos.x)*i_time/2;
		if((it->dpos.y-it->pos.y)>100)
			motion.y=100*i_time*(it->dpos.y-it->pos.y)/fabs(it->dpos.y-it->pos.y);
		else
			motion.y=(it->dpos.y-it->pos.y)*i_time/2;
		CheckCollision(it->pos,it->size,motion,*it);
		if(motion.x>=0)
			it->rotation=acosf((-motion.y)/(pow(pow(motion.x,2)+pow(motion.y,2),1./2.)))*180/3.14;
		else
			it->rotation=360-acosf((-motion.y)/(pow(pow(motion.x,2)+pow(motion.y,2),1./2.)))*180/3.14;
		it->pos+=motion;
		if(pow(pow(it->pos.x-it->dpos.x,2)+pow(it->pos.y-it->dpos.y,2),1./2.)<=100)
		{
			it->dpos.x=250+rand()%(mapSize.x-250);
			it->dpos.y=250+rand()%(mapSize.y-250);
		}
		//cout<<"("<<it->pos.x<<";"<<it->pos.y<<")";
		it++;
	}
}

void CGameMap::countOffset(Vector2u i_windSize,Vector2f PlayerCoords,float i_time)
{
	cOffset+=(PlayerCoords-cOffset)*(i_time*2);
	offset.x=cOffset.x*mScale-float(i_windSize.x)/2.;
	offset.y=cOffset.y*mScale-float(i_windSize.y)/2.;
	/*offset.x+=(PlayerCoords.x-offset.x)*i_time*mScale-float(i_windSize.x)/2;
	offset.y+=(PlayerCoords.y-offset.y)*i_time*mScale-float(i_windSize.y)/2;*/
	if(offset.x<0)
		offset.x=0;
	if(offset.x>mapSize.x*mScale-i_windSize.x)
		offset.x=float(mapSize.x*mScale-i_windSize.x);
	if(offset.y<0)
		offset.y=0;
	if(offset.y>mapSize.y*mScale-i_windSize.y)
		offset.y=float(mapSize.y*mScale-i_windSize.y);
	if(offset.x<0)
		offset.x/=2.;
	if(offset.y<0)
		offset.y/=2.;
	printf("Offset: (%5.2f;%5.2f)\n",offset.x,offset.y);
}

void CGameMap::countScale(Vector2u i_windSize,float devourerRadius)
{
	mScale=1/(devourerRadius/50);
	if((mapSize.x*mScale<i_windSize.x)||(mapSize.y*mScale<i_windSize.y))
	{
		if(getMinSide(i_windSize))
		{
			mScale=float(i_windSize.x)/float(mapSize.x);
			cout<<" !X! "<<endl;
		}
		else
		{
			mScale=float(i_windSize.y)/float(mapSize.y);
			cout<<" !Y! "<<endl;
		}
	}
	printf("Scale=%5.2f\n",mScale);
}

void CGameMap::CheckCollision(Vector2f i_pos,float i_radius,Vector2f &i_motion)
{
	Vector2f pl(i_pos+i_motion);
	vector<mapObjectNode>::iterator it;
	for(it=obj.begin();it<obj.end();it++)
	{
		if((it->pos==i_pos)||(it->size<i_radius))
			continue;
		float cRadius=pow(pow(pl.x-it->pos.x,2)+pow(pl.y-it->pos.y,2),1./2.);
		float coll=cRadius-it->size-i_radius;
		if(coll<0)
		{
			Vector2f mCos;
			mCos.x=(pl.x-it->pos.x)/cRadius;
			mCos.y=(pl.y-it->pos.y)/cRadius;

			float nRadius=it->size+i_radius;
			i_motion.x=it->pos.x+(mCos.x*nRadius)-i_pos.x;
			i_motion.y=it->pos.y+(mCos.y*nRadius)-i_pos.y;
			pl=Vector2f(i_pos+i_motion);
		}
	}
}

void CGameMap::CheckCollision(Vector2f i_pos,float i_radius,Vector2f &i_motion,mapObjectNode &i_obj)
{
	Vector2f pl(i_pos+i_motion);
	vector<mapObjectNode>::iterator it;
	for(it=obj.begin();it<obj.end();it++)
	{
		if((it->pos==i_pos)||(it->size<i_radius))
			continue;
		float cRadius=pow(pow(pl.x-it->pos.x,2)+pow(pl.y-it->pos.y,2),1./2.);
		float coll=cRadius-it->size-i_radius;
		if(coll<0)
		{
			if(!it->good)
			{
				it->dSize+=i_obj.size*eatCoeffcient;
				i_obj.alive=false;
				i_obj.dSize=0;
				if(i_obj.good)
					amOfGood--;
				else
					amOfBad--;
				break;
			}
			Vector2f mCos;
			mCos.x=(pl.x-it->pos.x)/cRadius;
			mCos.y=(pl.y-it->pos.y)/cRadius;

			float nRadius=it->size+i_radius;
			i_motion.x=it->pos.x+(mCos.x*nRadius)-i_pos.x;
			i_motion.y=it->pos.y+(mCos.y*nRadius)-i_pos.y;
			pl=Vector2f(i_pos+i_motion);
		}
	}
}

bool CGameMap::CheckDamage(Vector2f i_pos,float i_radius)
{
	vector<mapObjectNode>::iterator it;
	for(it=obj.begin();it<obj.end();it++)
	{
		if(pow(pow(i_pos.x-it->pos.x,2)+pow(i_pos.y-it->pos.y,2),1./2.)<(it->size+i_radius))
		{
			if(!it->alive)
			{
				it++;
				continue;
			}
			if((!it->good)&&(it->size>i_radius))
			{
				return true;
			}
		}
	}
	return false;
}

Vector2f CGameMap::getOffset()
{
	return offset;
}

void CGameMap::setMapSize(Vector2i i_size)
{
	mapSize=i_size;
	obj.clear();
	amOfBad=amOfGood=0;
	if(cOffset==Vector2f(-1,-1))
		cOffset=Vector2f(mapSize.x/2,mapSize.y/2);
}

Vector2i CGameMap::getMapSize()
{
	return mapSize;
}

float CGameMap::getScale()
{
	return mScale;
}

bool CGameMap::getMinSide(Vector2u i_windSize)
{
	if(i_windSize.x>i_windSize.y)
		return true;
	return false;
}

void CGameMap::addObj(Vector2f i_pos,float i_size,Color i_color,bool i_good)
{
	if(
		((i_pos.x<0)||(i_pos.x>mapSize.x))
		||
		((i_pos.y<0)||(i_pos.y>mapSize.y))
		||
		((mapSize.x==0)||(mapSize.y==0))
		)
	{
		ostringstream mes;
		mes<<"Unable to create new map object in ("<<i_pos.x<<";"<<i_pos.y<<"), because it`s out of map border or map was not load!";
		sendToLog("CGameMap",mes.str());
		return;
	}
	mapObjectNode newElem;
	newElem.pos=i_pos;
	newElem.dpos=i_pos;
	newElem.size=0;
	newElem.dSize=i_size;
	newElem.rotation=0;
	newElem.color=i_color;
	newElem.good=i_good;
	newElem.alive=true;
	obj.push_back(newElem);
	if(i_good)
		amOfGood++;
	else
		amOfBad++;
	ostringstream mes;
	mes<<"Added new map object in ("<<newElem.pos.x<<";"<<newElem.pos.y<<")! Now is "<<obj.size()<<" objects!";
	sendToLog("CGameMap",mes.str());
}  
                                    
void CGameMap::autoFillObj(CPlayer *devourer)
{
	for(int i=amOfBad;i<maxAmOfObj/2;i++)
		addObj(Vector2f(float(250+rand()%(mapSize.x-250)),float(250+rand()%(mapSize.y-250))),float(devourer->getRadius()-10+rand()%30),Color::Red,false);
	for(int i=amOfGood;i<maxAmOfObj;i++)
		addObj(Vector2f(float(250+rand()%(mapSize.x-250)),float(250+rand()%(mapSize.y-250))),float(devourer->getRadius()-30+rand()%20),Color::Green,true);
		//addObj(Vector2f(500,200),10,Color::White);
}

void CGameMap::eatObj(Vector2f i_pos,float i_radius,CPlayer *devourer)
{
	vector<mapObjectNode>::iterator it=obj.begin();
	findCond.pos=i_pos;
	findCond.radius=i_radius;
	while((it=find_if(it,obj.end(),findCond))!=obj.end())
	{
		if(!it->alive)
		{
			it++;
			continue;
		}
		ostringstream mes;
		mes<<"Removed map object in ("<<it->pos.x<<";"<<it->pos.y<<")! Objects remaining "<<obj.size()-1<<" of "<<maxAmOfObj<<"!";
		sendToLog("CGameMap (obj)",mes.str());
		if(it->good)
		{
			devourer->eatObj(it->size);
			amOfGood--;
		}
		else
		{
			devourer->eatObj(-it->size);
			amOfBad--;
		}
		it->alive=false;
		it->dSize=0;
		it++;
	}
}

void CGameMap::eatAllObj(bool i_good)
{
	vector<mapObjectNode>::iterator it;
	for(it=obj.begin();it<obj.end();it++)
		if(it->good==i_good)
		{
			it->alive=false;
			it->dSize=0;
		}
	if(i_good)
		amOfGood=0;
	else
		amOfBad=0;
}

void CGameMap::levelUp()
{
	setMapSize(Vector2i(mapSize.x+250,mapSize.y+250));
	maxAmOfObj++;
	level++;
}

int CGameMap::getLevel()
{
	return level;
}

void CGameMap::reset()
{
	obj.clear();
	amOfBad=amOfGood=0;
	mapSize=Vector2i(0,0);
	cOffset=Vector2f(-1,-1);
	mScale=1;
	level=1;
}

CGameMap::CGameMap(void):mapSize(0,0),offset(0,0),cOffset(-1,-1),mScale(1),maxAmOfObj(5),amOfGood(0),amOfBad(0),level(1)
{
	goodT.loadFromFile("Data/Textures/grass.png");
	badT.loadFromFile("Data/Textures/enemy.png");
	goodS.setTexture(goodT);
	goodS.setTextureRect(IntRect(0,0,100,100));
	badS.setTexture(badT);
	badS.setTextureRect(IntRect(0,0,100,100));
}


CGameMap::~CGameMap(void)
{
	obj.clear();
}

