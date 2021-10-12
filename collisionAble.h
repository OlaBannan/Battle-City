#pragma once
#include <SFML\Graphics.hpp>
#include "macro.h"
#include <list>
#include <memory>

const float SpeedPlayer = 0.033f;
const float SpeedEnemy = 0.040f;
const float SpeedBullet = 0.015f;

class Tank;
class Bullet;
class Map;
class Sprite;


typedef std::unique_ptr<Tank> TankPtr;

class collisionAble {
public:
	Sprite & sprite;	// the class that stores pictures
	Map & map;			// class that stores the map

	// enum struct|class name : int { }	
	enum class Move : int { left, right, up, down, none };
	struct Pos{ int x; int y; } posMap;	// position relative to the map (which block)

	// updating the image relative to the return of the object
	virtual void updateImage() = 0;

	// Checking collisions with blocks and starting collisions with tanks
	virtual void checkCollision(std::list<TankPtr> &, std::list<Bullet> &);
	//virtual void checkCollision(std::list<TankPtr> &) final;

	// A purely virtual method that checks for collisions
    // with the selected block determined on the basis of the + position passed to the box
	virtual bool collision(Pos, sf::FloatRect &) = 0;

	// A purely virtual method that checks collisions with tanks and the player
	virtual bool colWithTanks(std::list<TankPtr> &, std::list<Bullet> &, float) = 0;
	//virtual bool colWithTanks(std::list<Bullet>, std::list<TankPtr> &, float) = 0;

	// object tax
	sf::Clock timer;	// timer limiting the object
	float speed;		// the rate of the next shift of the object

	sf::Vector2f pos;	// display position
	sf::Sprite spr;		// image of the object
	Move move;			// image status (which page the object is returned to)
	Move lastMove;		// last move (needed for bullets)
	const int objID;	// object ID number

	bool exist;	// specifies whether the object exists
	collisionAble(Sprite &, Map &, bool, int, Move);

	const bool player;

	virtual ~collisionAble(void){}
};

