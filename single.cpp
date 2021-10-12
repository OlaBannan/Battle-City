#include "single.h"
#include "sound.h"

extern Sound sound;

Single::Single(bool x, sf::Font & font, Map & map, Sprite & spr, sf::RenderWindow & wndow, Timer & FPSclock)
	: font{ font }, map{map}, spr{ spr }, wndow{ wndow }, FPSclock{ FPSclock }
{
	gameType = x;
}
void Single::runSingle(){
	map.initiateGame(gameType);
	FPSclock.StopClock();
	while (map.gameGood()){
		if (map.loadMap()==0)
			continue;
		while (map.checkGameStatus()){
			sound.updateSound(map.lvl.tanks);

			map.events(FPSclock);

			// adding tanks
			map.addPlayer1Tank();
			if(gameType) map.addPlayer2Tank();
			map.addEnemyTank();

			// collisions
			for (auto & tank : map.lvl.tanks){
				tank->checkMove();
				tank->checkCollision(map.lvl.tanks, map.lvl.bullets);
			}
			for (auto & bullet : map.lvl.bullets){
				bullet.checkCollision(map.lvl.tanks, map.lvl.bullets);
			}

			// removing "corpses"
			clearDeathObjects();

			// drawing
			wndow.clear();
			for (auto & tank : map.lvl.tanks){
				wndow.draw(*tank);
			}
			wndow.draw(map);
			for (auto & bullet : map.lvl.bullets){
				wndow.draw(bullet);
			}
			for (auto & x : map.lvl.explosions){
				wndow.draw(x);
			}

			FPSclock.draw(wndow);
			map.setInformationProperties();
			wndow.display();
		}
	}
	FPSclock.StopClock();
	sound.stopAll();
	map.endGame();
}
void Single::clearDeathObjects(){	
	// restoring the possibilities of shot to the tanks
	for (auto bullet : map.lvl.bullets){
		if (bullet.exist == false){
			for (auto & tank : map.lvl.tanks){
				if (bullet.objID == tank->objID){
					tank->canShoot = { true };
					break;
				}
			}
		}
	}	
// getting rid of bullets
BACK:
	for (auto  i = map.lvl.bullets.begin(); i != map.lvl.bullets.end(); i++){
		if (i->exist == false){
			map.lvl.bullets.erase(i);
			goto BACK;
		}
	}
	//map.lvl.bullets.erase(std::remove_if(map.lvl.bullets.begin(), map.lvl.bullets.end(),
	//	[](const Bullet & x)->bool{return x.exist == false; }), map.lvl.bullets.end());

	map.lvl.tanks.erase(std::remove_if(map.lvl.tanks.begin(), map.lvl.tanks.end(),
		[&](const TankPtr & x)->bool{return x->exist == false; }), map.lvl.tanks.end());

	map.lvl.explosions.erase(std::remove_if(map.lvl.explosions.begin(), map.lvl.explosions.end(),
		[&](Explosion & x)->bool{return x.stillExist() == false; }), map.lvl.explosions.end());
}