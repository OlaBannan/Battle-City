#pragma once
#include "tank.h"
#include "map.h"

class Player1 : public Tank{
public:
	// constructor
	Player1(std::list<Explosion> & explosions, std::list<Bullet> & bullets, Sprite & sprite, Map & map, bool isPlayer = true, int ID = 0, Move move = Move::up)
		: Tank{ explosions, bullets, sprite, map, isPlayer, ID, move }
	{
		speed = { SpeedPlayer };

		spr = sprite.tankYellow;
		InitialPlace();
	}
	
	virtual ~Player1(void){}

	// character movement method
	void checkMove();
	
	// Initial Place
	void InitialPlace();
	
};