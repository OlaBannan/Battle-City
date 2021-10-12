#include "bullet.h"
#include "map.h"
#include "sound.h"

extern Sound sound;

Bullet::Bullet(Sprite & spr, Map & map, sf::Vector2f tankPos, int ID, Move move, bool isPlayer)
: collisionAble{ spr, map, isPlayer, ID, move }
{
	speed = { SpeedBullet };

	this->spr = sprite.bullet;

	updateImage();

	setStartPos(tankPos);
}
void Bullet::draw(sf::RenderTarget & okno, sf::RenderStates st) const{
	okno.draw(spr);
}
bool Bullet::collision(Pos posMap, sf::FloatRect & box){
	Block collisionBlock = map.tab[posMap.y][posMap.x];

	if (box.intersects(collisionBlock.img.getGlobalBounds())){
		if (collisionBlock.move == Block::Move::notMoveAble){
			if (collisionBlock.type == Block::Type::EagleDEAD){
				spr.setPosition(pos);
				exist = { false };
				move = Move::none;
				return 1;
			}
			else if (collisionBlock.type == Block::Type::Eagle){
				sound.Sounds["Blok"].play();
				map.tab[posMap.y][posMap.x].shotEagle(map);
				spr.setPosition(pos);
				exist = { false };
				move = Move::none;
				return 1;
			}
			else{
				sound.Sounds["Blok"].play();
				map.tab[posMap.y][posMap.x].shotBlock(sprite);
				spr.setPosition(pos);
				exist = { false };
				move = Move::none;
				return 1;
			}
		}

		else if (collisionBlock.move == Block::Move::endMap){
			sound.Sounds["Blok"].play();
			spr.setPosition(pos);
			exist = { false };
			move = Move::none;
			return 1;
		}
	}
	return 0;
}


bool Bullet::colWithTanks(std::list<TankPtr> & tanks, std::list<Bullet> & bullets, float speed)
{
	sf::FloatRect box = this->spr.getGlobalBounds();

	switch (this->move){
	case Bullet::Move::left: box.left -= speed;
		break;
	case Bullet::Move::right: box.left += speed;
		break;
	case Bullet::Move::up: box.top -= speed;
		break;
	case Bullet::Move::down: box.top += speed;
		break;
	}
	// destroying the tanks
	for (auto & tank : tanks){
		if (box.intersects(tank->spr.getGlobalBounds())){
			if (this->player != tank->player){
				this->spr.setPosition(pos);
				this->exist = { false };
				tank->exist = { false };
				return 1;
			}
			else if (this->objID != tank->objID){
				this->spr.setPosition(pos);
				this->exist = { false };
				return 1;
			}
			else{
				this->spr.setPosition(box.left, box.top);
				return 1;
			}
		}
	}
	return colWithBullets(bullets, box);
}
void Bullet::setStartPos(sf::Vector2f tankPos){
	this->spr.setPosition(tankPos.x, tankPos.y);
	this->spr.scale(map.pr.scale, map.pr.scale);

	// check the size of the projectile (sprite) and calculate its half
	float picWidth = float(spr.getGlobalBounds().height / 2.0);

	switch (move){
	case collisionAble::Move::left:
		tankPos.y += map.pr.blockSize - picWidth;
		break;
	case collisionAble::Move::right:
		tankPos.x += map.pr.blockSize - picWidth;
		tankPos.y += map.pr.blockSize - picWidth;
		break;
	case collisionAble::Move::up:
		tankPos.x += map.pr.blockSize - picWidth;
		break;
	case collisionAble::Move::down:
		tankPos.x += map.pr.blockSize - picWidth;
		tankPos.y += map.pr.blockSize - picWidth;
		break;
	}
	pos = tankPos;
	this->spr.setPosition(pos.x, pos.y);
}
bool Bullet::colWithBullets(std::list<Bullet> & bullets, sf::FloatRect & box){
	for (auto  bullet = bullets.begin(); bullet != bullets.end(); bullet++){
		if (box.intersects(bullet->spr.getGlobalBounds())){
			if (this->player != bullet->player){
				this->spr.setPosition(pos);
				bullet->exist = exist = { false };
				return 1;
			}
			else if (this->objID != bullet->objID){
				this->spr.setPosition(pos);
				this->exist = { false };
				return 1;
			}
			else{
				this->spr.setPosition(box.left, box.top);
				return 1;
			}
		}
	}
	return 0;
}
void Bullet::updateImage(){
	switch (move){
	case collisionAble::Move::left:
		this->spr.setTextureRect(sf::IntRect(0, 0, 40, 40));
		break;
	case collisionAble::Move::right:
		this->spr.setTextureRect(sf::IntRect(40, 0, 40, 40));
		break;
	case collisionAble::Move::up:
		this->spr.setTextureRect(sf::IntRect(80, 0, 40, 40));
		break;
	case collisionAble::Move::down:
		this->spr.setTextureRect(sf::IntRect(120, 0, 40, 40));
		break;
	}
}

void Bullet::checkCollision(std::list<TankPtr> & tanks, std::list<Bullet> & bullets){
	// check the traffic clock, we do not want to
    // so that the tank cuts too fast: P
	if (timer.getElapsedTime().asSeconds() >= speed){

		// We check if the traffic happens at all
		if (move != Move::none){
			// If so, we pull out the box that surrounds the vehicle
            // to test if it will not hit the wrong block
			sf::FloatRect box = spr.getGlobalBounds(); // bullet's box 

			// Check the position of the bullet on the map
			posMap.x = int((spr.getPosition().x - map.pr.sides) / map.pr.blockSize);
			posMap.y = int((spr.getPosition().y - map.pr.topBot) / map.pr.blockSize);

			float speed{ map.pr.blockSize / 4.f };

			// we change the picture
			updateImage();

			bool COL{ false };

			// Collision with blocks relative to the direction of movement
			switch (move){
			case collisionAble::Move::left:
				box.left -= speed;
				posMap.x--;
				if (collision(posMap, box)) COL = { true };
				posMap.y++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
				break;
			case collisionAble::Move::right:
				box.left += speed;
				posMap.x += 1;
				if (collision(posMap, box)) COL = { true };
				posMap.y++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
				break;
			case collisionAble::Move::up:
				box.top -= speed;
				posMap.y--;
				if (collision(posMap, box)) COL = { true };
				posMap.x++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
				break;
			case collisionAble::Move::down:
				box.top += speed;
				posMap.y += 1;
				if (collision(posMap, box)) COL = { true };
				posMap.x++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
				break;
			}
			// check if there is a collision with the rest of the tanks
			if (colWithTanks(tanks, bullets, speed)) return;

			// If the collision did not appear, then move
            // the correct spite of the vehicle to the position of the box
            // and overwrite the main position
			pos.x = box.left;
			pos.y = box.top;
			spr.setPosition(box.left, box.top);

			// we reset the timer
			timer.restart();
		}
	}
	// If any "if" has knocked us out,
	// set the object to the default position
	spr.setPosition(pos);
}