#include "map.h"


void Block::setImg(Sprite & spr){
	switch (type){
	case Block::Type::air:			img = spr.air; break;
	case Block::Type::brick:		img = spr.brick; break;
	case Block::Type::stone:		img = spr.stone; break;
	case Block::Type::green:		img = spr.green; break;
	case Block::Type::water:		img = spr.water;  break;
	case Block::Type::road:			img = spr.road; break;
	case Block::Type::endMap:		img = spr.stone; break;
	case Block::Type::Eagle:		img = spr.Eagle; break;
	case Block::Type::EagleDEAD:	img = spr.EagleDead; break;
	}
}
void Block::setMoveMode(){
	switch (type){
	case Block::Type::air:		move = Move::moveAble; break;
	case Block::Type::green:	move = Move::moveAble; break;
	case Block::Type::water:	move = Move::water; break;
	case Block::Type::road:		move = Move::moveAble; break;
	case Block::Type::endMap:	move = Move::endMap; break;
	default: move = Move::notMoveAble; break;
	}
}

void Block::shotBlock(Sprite & spr){
	if (hardness > 0){
		hardness--;
	}
	else{ // if hardness == 0 
		type = Type::air;
		setImg(spr);
	}
}

void Block::setHardness(){
	switch (type){
	case Block::Type::brick: hardness = { Hardness1 }; break; // from the second shot 
	case Block::Type::stone: hardness = { Hardness3 }; break; // form the third shot
	case Block::Type::Eagle: hardness = { Hardness0 }; break; // from the first shot
	}
}
void Block::shotEagle(Map & map){
	sf::Vector2f position;
	for (int x = 0; x < 2; x++){
		for (int y = 0; y < 2; y++){
			position = map.tab[26 + y][14 + x].img.getPosition();
			map.tab[26 + y][14 + x].img = map.spr.EagleDead;
			map.tab[26 + y][14 + x].img.setTextureRect(sf::IntRect(x * 50,
				y * 50, 100, 100));
			map.tab[26 + y][14 + x].img.setPosition(position);
			map.tab[26 + y][14 + x].img.setScale(map.pr.scale, map.pr.scale);
			map.tab[26 + y][14 + x].move = Block::Move::notMoveAble;
			map.tab[26 + y][14 + x].type = Block::Type::EagleDEAD;
			map.tab[26 + y][14 + x].setHardness();
		}
	}
}