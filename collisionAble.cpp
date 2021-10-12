#include "collisionAble.h"
#include "sprite.h"
#include "map.h"

#include <iostream>

collisionAble::collisionAble(Sprite & spr, Map & map, bool player, int ID, Move move)
	:exist{true}, sprite{ spr }, map{ map }, player{ player }, objID{ ID }, move{ move }{}

void collisionAble::checkCollision(std::list<TankPtr> & tanks, std::list<Bullet> & bullets){
	// check the motion clock, we do not want the tank too fast: P
	if (timer.getElapsedTime().asSeconds() >= speed){

	
		if (move != Move::none){
			// pull out the box that surrounds the vehicle to be tested,
			//will it not hit the wrong block
			sf::FloatRect box = spr.getGlobalBounds(); // the tank's box 

			// Check the position of the tank on the map
			posMap.x = int((spr.getPosition().x - map.pr.sides) / map.pr.blockSize);
			posMap.y = int((spr.getPosition().y - map.pr.topBot) / map.pr.blockSize);

			float speed{ map.pr.blockSize / 4.f };

			// we change the picture
			updateImage();

			bool COL{ false };

			// Collision with blocks relative to the direction of movement
			switch (move){
			case collisionAble::Move::left:{
				box.left -= speed;
				posMap.x--;
				if (collision(posMap, box)) COL = { true };
				posMap.y++;
				if (collision(posMap, box)) COL = { true };
				posMap.y++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
			} break;
			case collisionAble::Move::right:{
				box.left += speed;
				posMap.x += 2;
				if (collision(posMap, box)) COL = { true };
				posMap.y++;
				if (collision(posMap, box)) COL = { true };
				posMap.y++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
			} break;
			case collisionAble::Move::up:{
				box.top -= speed;
				posMap.y--;
				if (collision(posMap, box)) COL = { true };
				posMap.x++;
				if (collision(posMap, box)) COL = { true };
				posMap.x++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
			} break;
		 	case collisionAble::Move::down:{
				box.top += speed;
				posMap.y += 2;
				if (collision(posMap, box)) COL = { true };
				posMap.x++;
				if (collision(posMap, box)) COL = { true };
				posMap.x++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
			} break;
			}

			// check if there is a collision with the rest of the tanks
			if (colWithTanks(tanks, bullets, speed)) return;

			// If the collision did not appear, then we move the proper 
			//spite of the vehicle to the position of the box and overwrite
			//the main position
			pos.x = box.left;
			pos.y = box.top;
			spr.setPosition(box.left, box.top);

			// we reset the timer
			timer.restart();
		}
	}
	// If any "if" has knocked us out, set the object to the default position
	spr.setPosition(pos); // the old position
}