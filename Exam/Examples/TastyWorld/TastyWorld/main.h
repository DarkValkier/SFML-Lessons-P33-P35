#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Title.h"


using namespace sf;
using namespace std;

#define logFileWay "log.txt"
#define eatCoeffcient 0.1
#define radiusDetection 2000

/*unsigned int windowWidth;
unsigned int windowHeight;*/
class CPlayer;
class CGameMap;

void sendToLog(const char i_module[32],string i_message);
void setFullScreen(bool i);
bool getFullScreen();