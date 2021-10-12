#include "enemy.h"

void Enemy::checkMove() {
	if (move == Move::none) {
		lastMove = move = Move(rand() % 4);
	}
	if (canShoot && std::rand() % 100 == false) {
		//std::cout << objID << std::endl;
		bullets.emplace_back(sprite, map, pos, objID, lastMove, player);
		canShoot = { false };
	}
}