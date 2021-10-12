#pragma once
#include <SFML\Graphics.hpp>
#include "macro.h"
#include "collisionAble.h"

class Map;

class Bullet : public sf::Drawable, public collisionAble {
public:
	Bullet(Sprite &, Map &, sf::Vector2f, int, Move, bool);

	void setStartPos(sf::Vector2f);
	virtual bool collision(Pos, sf::FloatRect &) final;
	virtual bool colWithTanks(std::list<TankPtr> &, std::list<Bullet> &, float) final;
	virtual void checkCollision(std::list<TankPtr> &, std::list<Bullet> &) override;

	// updating the image relative to the return of the object
	virtual void updateImage() final;

	bool colWithBullets(std::list<Bullet> &, sf::FloatRect &);
private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
};