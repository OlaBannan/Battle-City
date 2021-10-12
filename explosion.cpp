#include "explosion.h"
#include "map.h"
#include "tank.h"

Explosion::Explosion(Map & map, Tank & tank){

	if(!tank.player)
    	map.destroyedEnemey += 1;

	img = map.spr.wybuch;
	img.scale(map.pr.scale, map.pr.scale);
	img.setPosition(tank.pos);

	img.setTextureRect(sf::IntRect(0, 0, 100, 100));

	timer.restart();
	sound.Sounds["explosion"].play();
}

void Explosion::update(){
	if (timer.getElapsedTime().asSeconds() >= 0.4){
		if (imgNum < 2) imgNum++;
		img.setTextureRect(sf::IntRect(imgNum * 100, 0, 100, 100));
		timer.restart();
	}
}
bool Explosion::stillExist(){
	if (sound.Sounds["explosion"].getStatus() == sf::Sound::Status::Playing){
		update();
		return 1;
	}
	else return 0;
}
void Explosion::draw(sf::RenderTarget & wndow, sf::RenderStates) const{
	wndow.draw(img);
}