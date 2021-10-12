#include "player1.h"

void Player1::InitialPlace()
{
    move = Move::up;

	pos.x = float(map.pr.sides + map.pr.blockSize * 10);
	pos.y = float(map.pr.topBot + map.pr.blockSize * 26);

	spr.setPosition(pos);
	spr.setScale(map.pr.scale, map.pr.scale);

	updateImage();
}

void  Player1::checkMove() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		lastMove = move = Move::up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		lastMove = move = Move::down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		lastMove = move = Move::left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		lastMove = move = Move::right;
	}
	else { // to save the right image of the tank if it doesn't move 
		if (move != Move::none) lastMove = move;
		move = Move::none;
	}
	
}