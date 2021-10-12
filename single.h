#pragma once
#include "sprite.h"
#include "map.h"
#include "Clock.h"
//#include <list>

//#include "level.h"
//#include "player.h"
//#include "enemy.h"
//#include "tank.h"
//#include "bullet.h"

class Single{
public:
	void runSingle();
	Single(bool, sf::Font &, Map &, Sprite &, sf::RenderWindow &, Timer &);
private:
	bool gameType;
	sf::Font & font;	
	Map & map;			// reference to the map
	Sprite & spr;				// reference to the class holding the pictures
	sf::RenderWindow & wndow;	// reference to the window
	Timer & FPSclock;
	
	void clearDeathObjects();
};