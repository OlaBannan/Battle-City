#pragma once
#include "collisionAble.h"

const int PlayerLives = 3;

class Explosion;

class Tank : public sf::Drawable, public collisionAble {
public:
	bool readyToShoot{ true };
	//construtor
	Tank(std::list<Explosion> &, std::list<Bullet> &, Sprite &, Map &, bool isPlayer = true, int ID = 0, Move move = Move::up);
	virtual ~Tank(void);

	//determines the character's movement
	virtual void checkMove() = 0;

	// check if there is a collision with the selected block
    // determined based on the position + passed box 
	virtual bool collision(Pos, sf::FloatRect &) final;

	// Checking the collision with the rest of the tanks
	virtual bool colWithTanks(std::list<TankPtr> &, std::list<Bullet> &, float) final;
	//virtual bool colWithTanks(std::list<TankPtr> &, float) final;

	// Checking the collision during the spawn of the vehicle
	virtual bool spawnCollision(std::list<TankPtr> &) final;

	// updating the image relative to the tank return
	virtual void updateImage() final;

	// bullet
	std::list<Bullet> & bullets;
	virtual void InitialPlace() {};
	bool canShoot{ true };
private:
	std::list<Explosion> & explosions;
	virtual void draw(sf::RenderTarget & wndow, sf::RenderStates states) const;
};