#pragma once
#include "sprite.h"
#include "macro.h"

const int  Hardness1 = 1;
const int  Hardness3 = 3;
const int  Hardness0 = 0;

class Map;

class Block{
public:
	enum class Type{ air, brick, stone, green, water, road, endMap, Eagle, EagleDEAD } type;
	enum class Move{ moveAble, notMoveAble, water, endMap } move;
	enum class Pos{ pos1, pos2, pos3, pos4 } pos;

	sf::Sprite img;
	bool hide{ false };

	void setImg(Sprite & spr);
	void setHardness();
	void setMoveMode();
	void shotBlock(Sprite & spr);
	void shotEagle(Map & map);
private:
	int hardness{ Hardness0 };
};