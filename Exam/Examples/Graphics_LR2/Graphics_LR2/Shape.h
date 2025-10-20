#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>

#pragma once

using namespace sf;
using namespace std;

struct PointsNode
{
	Vector3f pos;
	Color color;
};

class CShape
{
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;

	Vector3f positionFact;
	Vector3f rotationFact;
	Vector3f scaleFact;

	Vector3f moveDir;
	Vector3f rotationDir;
	Vector3f scaleDir;

	float curveMoveVar;

	Vector2f windowSize;
	Vector2i mousePosition;
	Vector3f centerPoint;

	sf::VertexArray line;
	sf::VertexArray quad;

	char* sourseFile;
	vector<PointsNode> points;

	void Multiply(double** m, double* p);
	void Multiply(double* p,double** m);

	Vector2f viewToScreen(Vector3f p);
	Vector3f movePoint(Vector3f p, Vector3f d);
	Vector3f scalePoint(Vector3f p, Vector3f s);
	Vector3f rotatePoint(Vector3f p, Vector3f r);
	void loadFromFile(char *file);
	bool outOfArea();

	void mirror(bool x,bool y,bool z);

public:
	void scaleCam(float scale);
	void update(float time);
	void draw(RenderWindow *wind);
	CShape(char* shapeFile,Vector3f centerPoint,Vector2f windowSize);
	CShape(void);
	~CShape(void);
};

