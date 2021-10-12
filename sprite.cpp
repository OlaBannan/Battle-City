#include "sprite.h"

Sprite::Sprite(void){
	load = { false };
	if (!airTx.loadFromFile("data/blocks/airTx.png")) return;
	if (!brickTx.loadFromFile("data/blocks/brickTx.gif")) return;
	if (!stoneTx.loadFromFile("data/blocks/stoneTx.gif")) return;
	if (!stoneBigTx.loadFromFile("data/blocks/stoneBigTx.gif")) return;
	if (!greenTx.loadFromFile("data/blocks/greenTx.png")) return;
	if (!waterTx.loadFromFile("data/blocks/waterTx.gif")) return;
	//if (!roadTx.loadFromFile("data/roadTx_beta.jpg")) return;

	// things from the menu
	if (!backGroundTx.loadFromFile("data/battle-city_title.png")) return;

	if (!controlTx.loadFromFile("data/control.png")) return;

	// tank images
	if (!tankGreenTx.loadFromFile("data/tanks/tankGreenTx.png")) return;
	if (!tankYellowTx.loadFromFile("data/tanks/tankYellowTx.png")) return;
	if (!tankRedTx.loadFromFile("data/tanks/tankRedTx.png")) return;
	if (!tankGreyTx.loadFromFile("data/tanks/tankGreyTx.png")) return;

	// bullet
	if (!bulletTx.loadFromFile("data/bulletTx.png")) return;

	// eagle
	if (!EagleTx.loadFromFile("data/kurak/kurakTx.png")) return;
	if (!EagleDeadTx.loadFromFile("data/kurak/kurakDeadTx.png")) return;

	// explosion
	if (!wybuchTx.loadFromFile("data/wybuchTx.gif")) return;

	load = { true };

	// load textures for sprites
    // blocks
	air.setTexture(airTx);
	brick.setTexture(brickTx);
	stone.setTexture(stoneTx);
	stoneBig.setTexture(stoneBigTx);
	green.setTexture(greenTx);
	water.setTexture(waterTx);
	//road.setTexture(roadTx);

	//manu
	backGround.setTexture(backGroundTx);
	control.setTexture(controlTx);
	tankIco.setTexture(tankYellowTx);
	tankIco.setTextureRect(sf::IntRect(200, 0, 100, 100));
	tankIco.rotate(90);



	// tanks
	tankGreen.setTexture(tankGreenTx);
	tankYellow.setTexture(tankYellowTx);
	tankRed.setTexture(tankRedTx);
	tankGrey.setTexture(tankGreyTx);

	// bullet
	bullet.setTexture(bulletTx);

	// eagle
	Eagle.setTexture(EagleTx);
	EagleDead.setTexture(EagleDeadTx);

	// explosion
	wybuch.setTexture(wybuchTx);
}