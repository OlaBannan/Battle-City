#pragma once
#include "tank.h"
#include "map.h"


class Enemy : public Tank{
public:
	// The status of the tank movement in the following scheme:
	// 1. First down (to a certain length)
	// 2. If the specified length is stopped or passed, then point 3
	// 3. Selects the left move
	// 4. If I can not move it to the right
	// 4. ...
	enum class MoveState { down, left, right, up };

	// constructor 
	Enemy(std::list<Explosion> & explosions, std::list<Bullet> & bullets, Sprite & sprite, Map & map, int ID, Level::NewTankPos tankPos, bool isPlayer = false, Move move = Move::down)
	: Tank{ explosions, bullets, sprite, map, isPlayer, ID, move }
{
	speed = { SpeedEnemy };

	if (std::rand() % 2) spr = sprite.tankGrey;
	else spr = sprite.tankRed;

	// choose the position
	switch (tankPos) {
	case Level::NewTankPos::left: {
		pos.x = float(map.pr.sides + map.pr.blockSize * 2);
		pos.y = float(map.pr.topBot + map.pr.blockSize);
	} break;
	case Level::NewTankPos::mid: {
		pos.x = float(map.pr.sides + map.pr.blockSize * 14);
		pos.y = float(map.pr.topBot + map.pr.blockSize);
	} break;
	case Level::NewTankPos::right: {
		pos.x = float(map.pr.sides + map.pr.blockSize * 26);
		pos.y = float(map.pr.topBot + map.pr.blockSize);
	} break;
	}

	spr.setPosition(pos.x, pos.y);
	spr.setScale(map.pr.scale, map.pr.scale);

	updateImage();

	lastMove = move;
}

	//destructor
	virtual ~Enemy( ){}

	//movement method
	void checkMove();
};