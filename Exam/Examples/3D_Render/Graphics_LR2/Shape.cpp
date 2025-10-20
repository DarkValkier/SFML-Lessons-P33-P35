#include "Shape.h"

void CShape::loadFromFile(char* file)
{
	PointsNode newElem;
	char buff[256];
	ifstream fin(file);

	if(!fin.is_open())
	{
		cout<<" Could not open file!"<<endl;
		system("pause");
	}
	else
	{
		points.clear();
		while(!fin.eof())
		{
			fin >> buff;
			newElem.pos.x = (float)atoi(buff);
			fin >> buff;
			newElem.pos.y = (float)atoi(buff);
			fin >> buff;
			newElem.pos.z = (float)atoi(buff);
			fin >> buff;
			newElem.color.r = atoi(buff);
			fin >> buff;
			newElem.color.g = atoi(buff);
			fin >> buff;
			newElem.color.b = atoi(buff);

			fin.getline(buff,256,'\n');

			this->points.push_back(newElem);
		}
		//cout<<"Points amount:"<<points.size()<<endl;
	}
}

Vector2f CShape::viewToScreen(Vector3f p)
{
	p=this->movePoint(p,this->position);
	p=this->rotatePoint(p,Vector3f(0,this->rotation.y,0));
	p=this->rotatePoint(p,Vector3f(this->rotation.x,0,this->rotation.z));
	p=this->scalePoint(p,this->scale);
	Vector2f result;
	
	result.x = p.x / (1 - (p.z / this->centerPoint.z)) + this->centerPoint.x;
	result.y = p.y / (1 - (p.z / this->centerPoint.z)) + this->centerPoint.y;

	return result;
}

void CShape::Multiply(double** m, double* p)
{
	double* result = new double[4];
	for (int i = 0; i < 4; i++)
	{
		result[i] = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i] = result[i] + (m[i][j] * p[i]);
		}
	}

	for(int i=0;i<4;i++)
		p[i]=result[i];

	delete result;
}

void CShape::Multiply(double* p,double** m)
{
	double* result = new double[4];
	for (int i = 0; i < 4; i++)
	{
		result[i] = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i] = result[i] + (p[j] * m[j][i]);
		}
	}

	for(int i=0;i<4;i++)
		p[i]=result[i];

	delete result;
}

Vector3f CShape::movePoint(Vector3f p, Vector3f d)
{
	double **m = new double*[4];

	for(int i=0;i<4;i++)
		m[i]=new double[4];

	double *result = new double[4];

	result[0]=p.x;
	result[1]=p.y;
	result[2]=p.z;
	result[3]=1;

	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = d.x;
	m[3][1] = d.y;
	m[3][2] = d.z;
	m[3][3] = 1;

	this->Multiply(result, m);

	p=Vector3f((float)result[0],(float)result[1], (float)result[2]);

	for(int i=0;i<4;i++)
		delete m[i];

	delete m;

	delete result;

	return p;
}

Vector3f CShape::scalePoint(Vector3f p, Vector3f s)
{
	double **m = new double*[4];

	for(int i=0;i<4;i++)
		m[i]=new double[4];

	double *result = new double[4];

	result[0]=p.x;
	result[1]=p.y;
	result[2]=p.z;
	result[3]=1;

	m[0][0] = s.x;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = s.y;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = s.z;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;

	this->Multiply(result, m);

	p=Vector3f((float)result[0], (float)result[1], (float)result[2]);

	for(int i=0;i<4;i++)
		delete m[i];

	delete m;

	delete result;

	return p;
}

Vector3f CShape::rotatePoint(Vector3f p, Vector3f r)
{
	double **m = new double*[4];

	for(int i=0;i<4;i++)
		m[i]=new double[4];

	double *result = new double[4];

	result[0]=p.x;
	result[1]=p.y;
	result[2]=p.z;
	result[3]=1;
	double rad;

	m[0][3] = 0;
	m[1][3] = 0;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;

	rad = 3.14 * r.x / 180;
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[1][0] = 0;
	m[1][1] = (float)cos(rad);
	m[1][2] = (float)sin(rad);
	m[2][0] = 0;
	m[2][1] = -(float)sin(rad);
	m[2][2] = (float)cos(rad);
	this->Multiply(result, m);

	rad = 3.14 * r.y / 180;
	m[0][0] = (float)cos(rad);
	m[0][1] = 0;
	m[0][2] = -(float)sin(rad);
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[2][0] = (float)sin(rad);
	m[2][1] = 0;
	m[2][2] = (float)cos(rad);
	this->Multiply(result, m);


	rad = 3.14 * r.z / 180;
	m[0][0] = (float)cos(rad);
	m[0][1] = (float)sin(rad);
	m[0][2] = 0;
	m[1][0] = -(float)sin(rad);
	m[1][1] = (float)cos(rad);
	m[1][2] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	this->Multiply(result, m);

	Vector3f ret(result[0],result[1],result[2]);

	for(int i=0;i<4;i++)
		delete m[i];

	delete m;

	delete result;

	return ret;
}

bool CShape::outOfArea()
{
	bool ret=false;
	vector<PointsNode>::iterator it=this->points.begin();

	while((it<this->points.end())&&!ret)
	{
		if(
			(this->viewToScreen(it->pos).x<0)||(this->viewToScreen(it->pos).x>this->windowSize.x)
			||
			(this->viewToScreen(it->pos).y<0)||(this->viewToScreen(it->pos).y>this->windowSize.y)
			)
			ret=true;

		it++;
	}
	return ret;
}

void CShape::scaleCam(float scale)
{
	this->scaleFact+=Vector3f(scale,scale,scale);
	if(this->scaleFact.x<0.3)
		this->scaleFact=Vector3f(0.3,0.3,0.3);
	if(this->scaleFact.x>1.4)
		this->scaleFact=Vector3f(1.4,1.4,1.4);
}

void CShape::mirror(bool x,bool y,bool z)
{
	
}

void CShape::update(float time)
{	
	cout<<" === UPDATE ==="<<endl<<endl;
	cout<<"SCALE:("<<this->scale.x<<";"<<this->scale.y<<";"<<this->scale.z<<")"<<endl;

	double speed=20;

	if(Keyboard::isKeyPressed(Keyboard::W))
		moveDir.y-=speed*time;
	if(Keyboard::isKeyPressed(Keyboard::S))
		moveDir.y+=speed*time;

	if(Keyboard::isKeyPressed(Keyboard::A))
		moveDir.x-=speed*time;
	if(Keyboard::isKeyPressed(Keyboard::D))
		moveDir.x+=speed*time;

	if(Keyboard::isKeyPressed(Keyboard::Q))
		moveDir.z-=speed*time;
	if(Keyboard::isKeyPressed(Keyboard::E))
		moveDir.z+=speed*time;

	if(Keyboard::isKeyPressed(Keyboard::I))
		scaleDir.y-=0.1*time;
	if(Keyboard::isKeyPressed(Keyboard::K))
		scaleDir.y+=0.1*time;

	if(Keyboard::isKeyPressed(Keyboard::J))
		scaleDir.x-=0.1*time;
	if(Keyboard::isKeyPressed(Keyboard::L))
		scaleDir.x+=0.1*time;

	if(Keyboard::isKeyPressed(Keyboard::U))
		scaleDir.z-=0.1*time;
	if(Keyboard::isKeyPressed(Keyboard::O))
		scaleDir.z+=0.1*time;

	if(Keyboard::isKeyPressed(Keyboard::F))
		scaleDir.x=-1;
	if(Keyboard::isKeyPressed(Keyboard::G))
		scaleDir.y=-1;
	if(Keyboard::isKeyPressed(Keyboard::H))
		scaleDir.z=-1;

	if(Mouse::isButtonPressed(Mouse::Button::Left))
	{
		if(Keyboard::isKeyPressed(Keyboard::X))
			rotationDir.x+=-Mouse::getPosition().y+mousePosition.y;
		else if(Keyboard::isKeyPressed(Keyboard::Z))
			rotationDir.z+=Mouse::getPosition().x-mousePosition.x;
		else
			rotationDir.y+=Mouse::getPosition().x-mousePosition.x;
	}

	if(Mouse::isButtonPressed(Mouse::Button::Right))
	{
			rotationFact.x-=-Mouse::getPosition().y+mousePosition.y;
			rotationFact.y-=Mouse::getPosition().x-mousePosition.x;
	}

	if(Keyboard::isKeyPressed(Keyboard::C))
	{
		this->curveMoveVar++;
		if(this->curveMoveVar>30)
			this->curveMoveVar=0;
		this->moveDir=Vector3f(-this->curveMoveVar,0,0);
		this->rotationDir=Vector3f(0.f,5.f,0.f);
	}

	if(Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->loadFromFile(this->sourseFile);
		this->curveMoveVar = 0;
	}

	vector<PointsNode>::iterator it;

	int i=0;
	cout<<" -- Modify ---"<<endl;
	for(it=points.begin();it<points.end();it++,i++)
		{
			//cout<<"Point "<<i<<": "<<it->pos.x<<":"<<it->pos.y<<":"<<it->pos.z<<" -> ";
			it->pos=this->movePoint(it->pos,this->moveDir);
			it->pos=this->rotatePoint(it->pos,this->rotationDir);
			it->pos=this->scalePoint(it->pos,this->scaleDir);
			//cout<<it->pos.x<<":"<<it->pos.y<<":"<<it->pos.z<<endl;
		}
	if(this->outOfArea())
	{
		for(it=points.begin();it<points.end();it++)
		{
			it->pos=this->movePoint(it->pos,-this->moveDir);
			it->pos=this->rotatePoint(it->pos,-this->rotationDir);
			it->pos=this->scalePoint(it->pos,Vector3f(1,1,1)-(this->scaleDir-Vector3f(1,1,1)));
		}
	}

	// == Обнуление переменных для следующего обновления ==
	this->mousePosition = Mouse::getPosition();

	this->moveDir=Vector3f(0,0,0);
	this->rotationDir=Vector3f(0,0,0);
	this->scaleDir=Vector3f(1,1,1);

	// == Плавное движение ==
	this->scale.x+=(this->scaleFact.x-this->scale.x)/5;
	this->scale.y+=(this->scaleFact.y-this->scale.y)/5;
	this->scale.z+=(this->scaleFact.z-this->scale.z)/5;

	this->rotation.x+=(this->rotationFact.x-this->rotation.x)/5;
	this->rotation.y+=(this->rotationFact.y-this->rotation.y)/5;
	this->rotation.z+=(this->rotationFact.z-this->rotation.z)/5;

	if(this->rotation.x>0)
	{
		this->rotationFact.x=this->rotation.x=0;
	}
}

void CShape::draw(RenderWindow *wind)
{	
	line[0].color=line[1].color=Color::Color(0,255,0,255);

	line[0].position = this->viewToScreen(Vector3f(0,500,0));
	line[1].position = this->viewToScreen(Vector3f(0,-500,0));
	wind->draw(line);

	line[0].color=line[1].color=Color::Color(255,0,0,255);
	line[0].position = this->viewToScreen(Vector3f(500,0,0));
	line[1].position = this->viewToScreen(Vector3f(-500,0,0));
	wind->draw(line);

	line[0].color=line[1].color=Color::Color(0,0,255,255);
	line[0].position = this->viewToScreen(Vector3f(0,0,-500));
	line[1].position = this->viewToScreen(Vector3f(0,0,500));
	wind->draw(line);

	quad[0].position=this->viewToScreen(Vector3f(-500,0,-500));
	quad[1].position=this->viewToScreen(Vector3f(-500,0,500));
	quad[2].position=this->viewToScreen(Vector3f(500,0,500));
	quad[3].position=this->viewToScreen(Vector3f(500,0,-500));
	wind->draw(quad);

	vector<PointsNode>::iterator it;

	int i=0;

	for(it=this->points.begin();it<this->points.end()-1;it++,i++)
	{
		//cout<<"Point "<<i<<":"<<this->viewToScreen(it->pos).x<<":"<<this->viewToScreen(it->pos).x<<endl;
		line[0].position = this->viewToScreen(it->pos);
		line[0].color = it->color;
		if((it+1)!=this->points.end())
		{
			line[1].position = this->viewToScreen((it+1)->pos);
			line[1].color = (it+1)->color;
		}
		else
		{
			line[1].position = this->viewToScreen(this->points.begin()->pos);
			line[1].color = this->points.begin()->color;
		}

		wind->draw(line);
	}
}

CShape::CShape(char* shapeFile,Vector3f centerPoint,Vector2f windowSize):centerPoint(centerPoint),windowSize(windowSize),sourseFile(shapeFile)
{
	this->position = Vector3f(0,0,0);
	this->rotation = Vector3f(0, 0, 0);
    this->scale = Vector3f(1, 1, 1);

	this->positionFact = Vector3f(0,0,0);
	this->rotationFact = Vector3f(0, 0, 0);
    this->scaleFact = Vector3f(1, 1, 1);

	this->moveDir=Vector3f(0,0,0);
	this->rotationDir=Vector3f(0,0,0);
	this->scaleDir=Vector3f(1,1,1);

	this->curveMoveVar = 0;

	this->line = sf::VertexArray(sf::Lines,2);
	line[0].color = sf::Color::Red;
	line[1].color = sf::Color::Red;

	this->quad = sf::VertexArray(sf::Quads,4);
	quad[0].color = sf::Color::Color(255,255,255,70);
	quad[1].color = sf::Color::Color(255,255,255,70);
	quad[2].color = sf::Color::Color(255,255,255,70);
	quad[3].color = sf::Color::Color(255,255,255,70);

	this->loadFromFile(this->sourseFile);
	this->mousePosition = Mouse::getPosition();
}

CShape::CShape(void)
{
	this->centerPoint=Vector3f(400.f,300.f,1000);

	this->position = Vector3f(0,0,0);
	this->rotation = Vector3f(0, 0, 0);
    this->scale = Vector3f(1, 1, 1);

	this->positionFact = Vector3f(0,0,0);
	this->rotationFact = Vector3f(0, 0, 0);
    this->scaleFact = Vector3f(1, 1, 1);

	this->moveDir=Vector3f(0,0,0);
	this->rotationDir=Vector3f(0,0,0);
	this->scaleDir=Vector3f(1,1,1);

	this->curveMoveVar = 0;

	this->windowSize = Vector2f(800.f,600.f);
	this->mousePosition = Mouse::getPosition();
}

CShape::~CShape(void)
{
}
