#pragma once
#include "Clock.h"
#include <array>
#include "macro.h"
#include "sprite.h"
#include "block.h"
#include "tank.h"
#include "bullet.h"
#include "explosion.h"
#include <iostream>


const int blockSIZE{ 30 };
typedef std::array < Block, blockSIZE > Blocks;
// BlockTab = typedef std::array < Blocks, blockSIZE > an array with size blockSIZE 
//2D array
typedef std::array < Blocks, blockSIZE > BlockTab; 

struct Window{
	int topBot;		    // empty space at the top and bottom of the screen
	int sides;		    // blank field on the left and right of the screen
	int blockSize;		// block size after reduction
	int sideMenu;		// width of the side panel
	float scale;		// scale of the block relative to its base dimension
	int widthInBlocks;	// the width of the map in blocks
};
struct Level{
	enum class NewTankPos{ left, mid, right } actualPos;

	std::list<TankPtr> tanks;
	std::list<Bullet> bullets;
	std::list<Explosion> explosions;

	int levelCount;
	int actualLevel{ 0 };
	int tanksID{ 2 };
	int enemyTanks;
	int playerTanks{ 3 };
	int enemyDestroyed{ 0 };
	sf::Clock timerPlayer1;
	sf::Clock timerPlayer2;
	sf::Clock timerEnemy;
	Level(int levelCount = 1) : levelCount{ levelCount }{}
};

class Map : public sf::Drawable{
public:
	Map(Sprite &, Timer & FPSclock ,sf::RenderWindow &);
	enum class Sett { left, up, right, down, corner1, corner2, corner3, corner4, cornerBig1, cornerBig2, cornerBig3, cornerBig4, full };
	enum class GameState{ game, nextLevel, gameOver, exit };
	Window pr;
	BlockTab tab;
	Sprite & spr;
	Timer &GameClock;
	sf::RenderWindow & wndow;
	Level lvl;
	int destroyedEnemey{ 0 };

	void setProperties(sf::RenderWindow & wndow){
		pr.blockSize = int(wndow.getSize().y / 30);
		pr.topBot = (wndow.getSize().y - pr.blockSize * 30) / 2;
		pr.sideMenu = int((wndow.getSize().x - pr.blockSize * 30) / pr.blockSize) * pr.blockSize;
		pr.sides = (wndow.getSize().x - pr.blockSize * 30 - pr.sideMenu) / 2;
		pr.scale = float(pr.blockSize / 50.0);
		pr.widthInBlocks = 30 + pr.sideMenu / pr.blockSize;
	}
	void setSpritesProperties(){
		for (int y = 0; y < blockSIZE; y++){
			for (int x = 0; x < blockSIZE; x++){
				tab[y][x].setImg(spr);
				tab[y][x].img.setPosition(float(x * pr.blockSize + pr.sides), float(y * pr.blockSize + pr.topBot));
				tab[y][x].img.setScale(pr.scale, pr.scale);
				tab[y][x].setHardness();
				tab[y][x].setMoveMode();
			}
		}
	}

	void setInformationProperties();

	int loadMap();
	void addEnemyTank();
	void addPlayer1Tank();
	void addPlayer2Tank();

	void events(Timer &);
	bool gameGood();
	bool checkGameStatus();
	void initiateGame(bool);
	void endGame();
	void setEagle(){
		for (int x = 0; x < 2; x++){
			for (int y = 0; y < 2; y++){
				sf::Vector2f position = tab[26 + y][14 + x].img.getPosition();
				tab[26 + y][14 + x].img = spr.Eagle;
				tab[26 + y][14 + x].img.setTextureRect(sf::IntRect(x * 50,
					y * 50, 100, 100));
				tab[26 + y][14 + x].img.setPosition(position);
				tab[26 + y][14 + x].img.setScale(pr.scale, pr.scale);
				tab[26 + y][14 + x].move = Block::Move::notMoveAble;
				tab[26 + y][14 + x].type = Block::Type::Eagle;
				tab[26 + y][14 + x].setHardness();
			}
		}
	}
	bool checkEagleIsLive(){
		if (tab[26][14].type == Block::Type::EagleDEAD) return 0;
		else return 1;
	}

	void nextLevel();
	void gameOver();
	void Won();
	void Exit();
private:
	GameState state;
    sf::Font font;
	sf::Text txt1, txt2 ,enmeisStr ,livesStr, level_;
	bool SecRoundPlus = false;
	int AliveEnemyTank;
	sf::Sprite sprPlayerTank;
	sf::Sprite sprEnemyTank;

	virtual	void draw(sf::RenderTarget & wndow, sf::RenderStates) const{
		for (auto y : tab){
			for (auto x : y){
				 if (x.hide) continue;
				wndow.draw(x.img);
			}
		}
	    
	}
};