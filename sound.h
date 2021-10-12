#pragma once
#include <unordered_map> 

#include <map>
#include <string>
#include <SFML\Audio.hpp>
#include "tank.h"

typedef std::unordered_map < std::string, sf::Sound > soundsMap;

class Sound{
private:
	std::map<int, sf::SoundBuffer> buffer;
public:
	// List of sounds:
	// ride, rest, gameOver, shot, arrowsBlok
	soundsMap Sounds;

	Sound(){
		int i{ 0 };

		buffer[i].loadFromFile("data/move.wav");
		Sounds["move"].setBuffer(buffer[i]); //jazda
		Sounds["move"].setLoop(true);
		Sounds["move"].setVolume(50);
		i++;

		buffer[i].loadFromFile("data/tank2.wav");
		Sounds["tank2"].setBuffer(buffer[i]); //spoczynek
		Sounds["tank2"].setLoop(true);
		Sounds["tank2"].setVolume(50);
		i++;

		buffer[i].loadFromFile("data/gameOver.wav");
		Sounds["gameOver"].setBuffer(buffer[i]);
		Sounds["gameOver"].setVolume(75);
		i++;

		buffer[i].loadFromFile("data/Winning.wav");
		Sounds["Winning"].setBuffer(buffer[i]);
		Sounds["Winning"].setVolume(75);
		i++;

		buffer[i].loadFromFile("data/shot.wav");
		Sounds["shot"].setBuffer(buffer[i]); //strza
		Sounds["shot"].setVolume(25);
		i++;

		buffer[i].loadFromFile("data/BlokV3.wav");
		Sounds["Blok"].setBuffer(buffer[i]);
		Sounds["Blok"].setVolume(75);
		i++;

		buffer[i].loadFromFile("data/explosion.wav");
		Sounds["explosion"].setBuffer(buffer[i]); //wybuch
		Sounds["explosion"].setVolume(100);
	}

	void updateSound(std::list<TankPtr> & tanks){
		bool jedziemy{ false };
		for (auto & tank : tanks){
			if (tank->move != Tank::Move::none){
				jedziemy = { true };
				break;
			}
		}
		if (jedziemy){
			if (Sounds["move"].getStatus() != sf::Sound::Status::Playing){
				Sounds["tank2"].stop();
				Sounds["move"].play();
			}
		}
		else{
			if (Sounds["tank2"].getStatus() != sf::Sound::Status::Playing){
				Sounds["move"].stop();
				Sounds["tank2"].play();
			}
		}
	}

	void stopAll(){
		Sounds["move"].stop();
		Sounds["tank2"].stop();
		Sounds["gameOver"].stop();
		Sounds["Winning"].stop();
		Sounds["shot"].stop();
		Sounds["Blok"].stop();
	}
};