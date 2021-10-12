#pragma once
#include <SFML/Graphics.hpp>
#include "macro.h"
#include "sound.h"


class Tank;
class Map;

extern Sound sound;

class Explosion : public sf::Drawable{
private:
	int imgNum{ 0 };
	sf::Clock timer;
	sf::Sprite img;

	void update();
public:

	Explosion(Map &, Tank &);
	bool stillExist();

private:
	virtual void draw(sf::RenderTarget & wndow, sf::RenderStates) const;
};