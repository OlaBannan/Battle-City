#pragma once
#include <SFML\Graphics.hpp>

class Sprite{
private:
	
	sf::Texture airTx;
	sf::Texture brickTx;
	sf::Texture stoneTx;
	sf::Texture stoneBigTx;
	sf::Texture greenTx;
	sf::Texture waterTx;
	//sf::Texture roadTx;

	// things from the menu

	sf::Texture backGroundTx;	// The background behind the title in the menu:>
	sf::Texture controlTx;

	// tank images

	sf::Texture tankGreenTx;
	sf::Texture tankYellowTx;
	sf::Texture tankRedTx;
	sf::Texture tankGreyTx;

	// bullet
	sf::Texture bulletTx;

	//Eagle
	sf::Texture EagleTx;
	sf::Texture EagleDeadTx;

	// explosion
	sf::Texture wybuchTx;

	bool load;
public:
	
	// blocks
	sf::Sprite air;
	sf::Sprite brick;
	sf::Sprite stone;
	sf::Sprite stoneBig;
	sf::Sprite green;
	sf::Sprite water;
	sf::Sprite road;


	// things from the menu

	sf::Sprite tankIco;
	sf::Sprite backGround;
	sf::Sprite control;

	// tank images

	sf::Sprite tankGreen;
	sf::Sprite tankYellow;
	sf::Sprite tankRed;
	sf::Sprite tankGrey;

	// bullet
	sf::Sprite bullet;

	// Eagle
	sf::Sprite Eagle;
	sf::Sprite EagleDead;

	// explosion
	sf::Sprite wybuch;

	bool isGood(){ return load; }
	Sprite(void);
};