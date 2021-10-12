#pragma once
#include "tank.h"
#include "map.h"

class Player2 : public Tank{
public:
	Player2(std::list<Explosion> & explosions, std::list<Bullet> & bullets, Sprite & sprite, Map & map, bool isPlayer = true, int ID = 1, Move move = Move::up)
		: Tank{ explosions, bullets, sprite, map, isPlayer, ID, move }
	{
		speed = { SpeedPlayer };

		spr = sprite.tankGreen;

		InitialPlace();
		//this->move = Move::none;
	}
	virtual ~Player2(void){}

	void checkMove() override;

	void InitialPlace();
};