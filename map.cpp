#include "map.h"
#include "player1.h"
#include "player2.h"
#include "enemy.h"
#include <fstream>
#include "sound.h"
#include <windows.h>


extern Sound sound;

Map::Map(Sprite & spr, Timer & FPSclock, sf::RenderWindow & wndow) : spr{ spr }, GameClock{FPSclock}, wndow{ wndow } {
    sprPlayerTank = spr.tankGreen;
	sprEnemyTank = spr.tankRed;

	sprEnemyTank.setTextureRect(sf::IntRect(200, 0, 100, 100));
	sprPlayerTank.setTextureRect(sf::IntRect(200, 0, 100, 100));
    sprEnemyTank.setPosition(float(1200), float(500));
    sprPlayerTank.setPosition(float(1200), float(800));
	setInformationProperties();
}

int Map::loadMap() {
	int type, sett;
	if (lvl.levelCount == 7) {
		Won();
		return 0;
	}
	else {
		if (lvl.levelCount == 1) {
			GameClock.restart();
			GameClock.switchClock();
		}

		for (auto & tank : lvl.tanks)
			if (tank->player)
				tank->InitialPlace();
			
		lvl.playerTanks = 3;
		
		std::string path = "data/levels/level" + std::to_string(lvl.levelCount) + ".txt";
		//std::cout << path << std::endl;
		std::fstream Plik(path, std::ios::in);

		Plik >> lvl.enemyTanks;
		AliveEnemyTank = lvl.enemyTanks;


		for (int y = 0; y < blockSIZE / 2; y++) {
			for (int x = 0, X = x * 2, Y = y * 2; x < blockSIZE / 2; x++, X = x * 2, Y = y * 2) {
				Plik >> type >> sett;
				//std::cout << "x: " << x << " X: "<< X << " y: " << y << " Y: " << Y << " Type: " << type <<  "Sett: "<< sett << std::endl;


				tab[Y][X].pos = Block::Pos::pos1;
				tab[Y][X + 1].pos = Block::Pos::pos2;
				tab[Y + 1][X + 1].pos = Block::Pos::pos3;
				tab[Y + 1][X].pos = Block::Pos::pos4;

				switch (Map::Sett(sett)) {
				case Map::Sett::left:
					tab[Y][X].type = tab[Y + 1][X].type = Block::Type(type);
					tab[Y][X + 1].type = tab[Y + 1][X + 1].type = Block::Type::air;
					break;
				case Map::Sett::up:
					tab[Y][X].type = tab[Y][X + 1].type = Block::Type(type);
					tab[Y + 1][X].type = tab[Y + 1][X + 1].type = Block::Type::air;
					break;
				case Map::Sett::right:
					tab[Y][X + 1].type = tab[Y + 1][X + 1].type = Block::Type(type);
					tab[Y][X].type = tab[Y + 1][X].type = Block::Type::air;
					break;
				case Map::Sett::down:
					tab[Y + 1][X].type = tab[Y + 1][X + 1].type = Block::Type(type);
					tab[Y][X].type = tab[Y][X + 1].type = Block::Type::air;
					break;
				case Map::Sett::corner1:
					tab[Y][X].type = Block::Type(type);
					tab[Y][X + 1].type = tab[Y + 1][X].type = tab[Y + 1][X + 1].type = Block::Type::air;
					break;
				case Map::Sett::corner2:
					tab[Y][X + 1].type = Block::Type(type);
					tab[Y][X].type = tab[Y + 1][X].type = tab[Y + 1][X + 1].type = Block::Type::air;
					break;
				case Map::Sett::corner3:
					tab[Y + 1][X + 1].type = Block::Type(type);
					tab[Y][X + 1].type = tab[Y + 1][X].type = tab[Y][X].type = Block::Type::air;
					break;
				case Map::Sett::corner4:
					tab[Y + 1][X].type = Block::Type(type);
					tab[Y][X + 1].type = tab[Y][X].type = tab[Y + 1][X + 1].type = Block::Type::air;
					break;
				case Map::Sett::cornerBig1:
					tab[Y + 1][X + 1].type = Block::Type::air;
					tab[Y][X + 1].type = tab[Y + 1][X].type = tab[Y][X].type = Block::Type(type);
					break;
				case Map::Sett::cornerBig2:
					tab[Y + 1][X].type = Block::Type::air;
					tab[Y][X + 1].type = tab[Y][X].type = tab[Y + 1][X + 1].type = Block::Type(type);
					break;
				case Map::Sett::cornerBig3:
					tab[Y][X].type = Block::Type::air;
					tab[Y][X + 1].type = tab[Y + 1][X].type = tab[Y + 1][X + 1].type = Block::Type(type);
					break;
				case Map::Sett::cornerBig4:
					tab[Y][X + 1].type = Block::Type::air;
					tab[Y][X].type = tab[Y + 1][X].type = tab[Y + 1][X + 1].type = Block::Type(type);
					break;
				case Map::Sett::full:
					tab[Y][X].type = tab[Y + 1][X].type = Block::Type(type);
					tab[Y][X + 1].type = tab[Y + 1][X + 1].type = Block::Type(type);
					break;
				}
			}
		}
		Plik.close();
		setSpritesProperties();
		setInformationProperties();
		setEagle();
		return 1;
	}
}
void Map::events(Timer & FPSclock){
	sf::Event event;
	while (wndow.pollEvent(event)){
		if (event.type == sf::Event::Closed) { exit(1); }
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
			state = GameState::exit;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T){
			FPSclock.switchClock();
		}
		// shoot player 1
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
			for (auto & tank : lvl.tanks){
				if (tank->objID == 0){
					if (tank->canShoot && tank->readyToShoot){
						tank->canShoot = tank->readyToShoot = { false };
						lvl.bullets.emplace_back(spr, *this, tank->pos, tank->objID, tank->lastMove, tank->player);
						sound.Sounds["shot"].play();
						break;
					}
				}
			}
		}
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space){
			for (auto & tank : lvl.tanks){
				if (tank->objID == 0){
					if (!tank->readyToShoot){
						tank->readyToShoot = { true };
						break;
					}
				}
			}
		}
		//shoot player 2 
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E){
			for (auto & tank : lvl.tanks){
				if (tank->objID == 1){
					if (tank->canShoot && tank->readyToShoot){
						tank->canShoot = tank->readyToShoot = { false };
						lvl.bullets.emplace_back(spr, *this, tank->pos, tank->objID, tank->lastMove, tank->player);
						sound.Sounds["shot"].play();
						break;
					}
				}
			}
		}
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::E){
			for (auto & tank : lvl.tanks){
				if (tank->objID == 1){
					if (!tank->readyToShoot){
						tank->readyToShoot = { true };
						break;
					}
				}
			}
		}
	}
}

void Map::setInformationProperties()
{
	font.loadFromFile("data/joystix monospace.ttf");
	txt1.setFont(font);
	txt1.setCharacterSize(wndow.getSize().y / 24);
	txt1.setFillColor(sf::Color::Red);
	txt1.setString("Enemies: ");
	txt1.setPosition(float(1200), float(400));

	level_.setFont(font);
	level_.setCharacterSize(wndow.getSize().y / 24);
	level_.setFillColor(sf::Color::Blue);
	level_.setString("Level: " + std::to_string(lvl.levelCount));
	level_.setPosition(float(1200), float(200));

	txt2.setFont(font);
	txt2.setCharacterSize(wndow.getSize().y / 24);
	txt2.setFillColor(sf::Color::White);
	txt2.setString("Lives: ");
	txt2.setPosition(float(1200), float(700));

	enmeisStr.setFont(font);
	enmeisStr.setCharacterSize(wndow.getSize().y / 24);
	enmeisStr.setFillColor(sf::Color::White);

	livesStr.setFont(font);
	livesStr.setCharacterSize(wndow.getSize().y / 24);
	livesStr.setFillColor(sf::Color::White);


	enmeisStr.setString(std::to_string(AliveEnemyTank - destroyedEnemey) + "/" + std::to_string(AliveEnemyTank));
	livesStr.setString(std::to_string(lvl.playerTanks));
	enmeisStr.setPosition(float(1350), float(515));
	livesStr.setPosition(float(1350), float(815));

	wndow.draw(txt1);
	wndow.draw(txt2);
	wndow.draw(enmeisStr);
	wndow.draw(livesStr);
	wndow.draw(enmeisStr);
	wndow.draw(livesStr);
	wndow.draw(level_);
	wndow.draw(sprEnemyTank);
	wndow.draw(sprPlayerTank);

}

bool Map::gameGood(){
	switch (state){
	case Map::GameState::game:		return 1;
	case Map::GameState::nextLevel: nextLevel();	return 1;
	case Map::GameState::gameOver:	gameOver();	lvl.levelCount = 1;	return 0;
	case Map::GameState::exit:		Exit(); lvl.levelCount = 1;     return 0;
	}
}

bool Map::checkGameStatus(){
	if (lvl.playerTanks == 1){
		if (std::count_if(lvl.tanks.begin(), lvl.tanks.end(),
			[&](const TankPtr & x)->bool{return x->player; }) == 0){
			state = GameState::gameOver;
			return 0;
		}
	}
	if (lvl.enemyTanks == 0){
		if (std::count_if(lvl.tanks.begin(), lvl.tanks.end(),
			[&](const TankPtr & x)->bool{return x->player == false; }) == 0){
			state = GameState::nextLevel;
			return 0;
		}
	}
	if (checkEagleIsLive() == false){
		state = GameState::gameOver;
		return 0;
	}
	if (state == GameState::exit) return 0;
	return 1;
}

void Map::addPlayer1Tank(){
	// player face 1
	if (lvl.playerTanks > 0){
		bool kakauko{ false };
		for (auto & tank : lvl.tanks){ // if already there is a tanks that related to the player on the map
			if (tank->exist == true && tank->objID == 0){
				kakauko = { true };
				break;
			}
		}
		if (!kakauko){
			if (lvl.timerPlayer1.getElapsedTime().asSeconds() >= 2.f){

				lvl.tanks.emplace_front(new Player1{ lvl.explosions, lvl.bullets, spr, *this });
				if (lvl.tanks.back()->spawnCollision(lvl.tanks)){
					lvl.tanks.pop_back();
				}
				else{
					if (SecRoundPlus) { // is it the second Round ?
						lvl.playerTanks--;
						lvl.timerPlayer1.restart();
					}
					else // it is the first round
						SecRoundPlus = true;
				}
			}
		}
	}
}
void Map::addPlayer2Tank(){
	//player's tank 2
	if (lvl.playerTanks > 0){
		bool kakauko{ false };
		for (auto & tank : lvl.tanks){
			if (tank->exist == true && tank->objID == 1){
				kakauko = { true };
				break;
			}
		}
		if (!kakauko){
			if (lvl.timerPlayer2.getElapsedTime().asSeconds() >= 2.f){

				lvl.tanks.emplace_front(new Player2{ lvl.explosions, lvl.bullets, spr, *this });
				if (lvl.tanks.back()->spawnCollision(lvl.tanks)){
					lvl.tanks.pop_back();
				}
				else{
					lvl.playerTanks--;
					lvl.timerPlayer2.restart();
				}
			}
		}
	}
}

void Map::addEnemyTank(){
	// check if we still have any tanks
	if (lvl.enemyTanks > 0 && lvl.tanks.size() - std::count_if(lvl.tanks.begin(), lvl.tanks.end(),
		[&](const TankPtr & x)->bool{return x->player; }) < 5){

		// check if any one has already appeared
		if (lvl.timerEnemy.getElapsedTime().asSeconds() >= 1.5f){
			// we set the position of the spawn tank
            // They are to appear successively: on the left, in the middle, on the right

			Level::NewTankPos temp = lvl.actualPos;
			switch (lvl.actualPos){
			case Level::NewTankPos::left:
				lvl.actualPos = Level::NewTankPos::mid;
				break;
			case Level::NewTankPos::mid:
				lvl.actualPos = Level::NewTankPos::right;
				break;
			case Level::NewTankPos::right:
				lvl.actualPos = Level::NewTankPos::left;
				break;
			default:
				break;
			}

			lvl.tanks.emplace_back(new Enemy{ lvl.explosions, lvl.bullets, spr, *this, lvl.tanksID, lvl.actualPos });
			if (lvl.tanks.back()->spawnCollision(lvl.tanks)){
				lvl.tanks.pop_back();
				lvl.actualPos = temp;
			}
			else{
				lvl.tanksID++;
				lvl.enemyTanks--;
				lvl.timerEnemy.restart();
			}
		}
	}
}
void Map::initiateGame(bool gameType){
	state = GameState::game;
	lvl.tanksID = { 2 };
	if (gameType) lvl.playerTanks = { 4 };
	else lvl.playerTanks = { 3 };
	destroyedEnemey = 0; 
	SecRoundPlus = false;
	lvl.timerEnemy.restart();
	lvl.actualPos = Level::NewTankPos::mid;
	setEagle();
}
void Map::endGame(){
	lvl.tanks.clear();
	lvl.bullets.clear();
}

void Map::nextLevel(){
	state = GameState::game;
	AliveEnemyTank = 0;
	lvl.levelCount += 1;
	SecRoundPlus = false;
	destroyedEnemey = 0;
	//loadMap();
}
void Map::Exit() {
	endGame();
	//state = GameState::exit;
}
void Map::Won()
{
	
	sf::Text Win;
	font.loadFromFile("data/joystix monospace.ttf");
	Win.setFont(font);
	Win.setCharacterSize(wndow.getSize().y / 24);
	Win.setFillColor(sf::Color::Blue);
	Win.setString("Yon Won");
	Win.rotate(-45);
	Win.setScale(sf::Vector2f(3.5, 3.5));
	Win.setPosition(float(50), float(700));

	sound.Sounds["Winning"].play();
	while (sound.Sounds["Winning"].getStatus() == sf::Sound::Status::Playing) {
		wndow.draw(Win);
		Sleep(1000);
		wndow.display();
	}

	state = GameState::exit;
}

void Map::gameOver() {
	
	sf::Text GameOver;
	font.loadFromFile("data/joystix monospace.ttf");
	GameOver.setFont(font);
	GameOver.setCharacterSize(wndow.getSize().y / 24);
	GameOver.setFillColor(sf::Color::Red);
	GameOver.setString("Game Over!");
	GameOver.rotate(-45);
	GameOver.setScale(sf::Vector2f(3.5, 3.5));
	GameOver.setPosition(float(50), float(900));
	
	sound.Sounds["gameOver"].play();
	while (sound.Sounds["gameOver"].getStatus() == sf::Sound::Status::Playing){
		wndow.draw(GameOver);
		Sleep(1000);
	    wndow.display();
     }

	state = GameState::exit;
}