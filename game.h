#pragma oncev
#include "Clock.h"
#include <Windows.h>
#include "single.h"
#include "sprite.h"
#include "map.h"
#include "block.h"
#include <tchar.h>

#define NOMINMAX

class Game{
public:
	enum class GameState { Menu, SinglePlayerGame, TwoPlayerGame, EXIT };
	void runGame(){
		while (state != GameState::EXIT){
			switch (state){
			case GameState::Menu:
				menu(); break;
			case GameState::SinglePlayerGame:
				game(0); break;
			case GameState::TwoPlayerGame:
				game(1); break;
			}
		}
	}
private:
	sf::RenderWindow wndow;

	GameState icon;		// needed to determine the position of the tank in the menu
	GameState state;	// current manu status of the game (menu, single, multi etc)

	Sprite spr;			// class that stores textures
	Map map;			// class displaying the map

	sf::Font font;		// needed font
	Timer FPSclock;

	// functions related to the menu
	void menu();
	void game(bool x){
		if (x == 0){
			Single single{ x, font, map, spr, wndow, FPSclock };
			single.runSingle();

			state = GameState::Menu;
		}
		else{
			Single single{ x, font, map, spr, wndow, FPSclock };
			single.runSingle();

			state = GameState::Menu;
		}
	}
	void eventsMenu();
public:
	Game(void) : map{ spr, FPSclock, wndow }, FPSclock{ font }{
		std::srand(unsigned(std::time(nullptr)));
		wndow.create(sf::VideoMode(1920, 1080), "Battle City", sf::Style::Fullscreen);
		wndow.setFramerateLimit(60);
		map.setProperties(wndow);

 		state = GameState::EXIT;
		if (!spr.isGood()){
			MessageBox(NULL, _T("Some image not found!"), _T("ERROR"), NULL);
			return;
		}
		if (!font.loadFromFile("data/joystix monospace.ttf")){
			MessageBox(NULL, _T("Font not found!"), _T("ERROR"), NULL);
			return;
		}
		state = GameState::Menu;
	}
};