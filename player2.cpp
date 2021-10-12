#include "player2.h"

void Player2::InitialPlace()
{
	move = Move::up ;
	

	pos.x = float(map.pr.sides + map.pr.blockSize * 17);
	pos.y = float(map.pr.topBot + map.pr.blockSize * 26);

	spr.setPosition(pos);
	spr.setScale(map.pr.scale, map.pr.scale);

	updateImage();
}


void Player2::checkMove() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		lastMove = move = Move::up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		lastMove = move = Move::down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		lastMove = move = Move::left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		lastMove = move = Move::right;
	}
	else {// to save the right image of the tank if it doesn't move 
		if (move != Move::none) lastMove = move;
		move = Move::none;
	}
}