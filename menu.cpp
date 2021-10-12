#include "game.h"

void Game::menu(){
	const int ILE{ 3 };
	sf::Text tekst[ILE];
	sf::String str[]{"1 player", "2 players", "Exit"};
	sf::Sprite menuStone = spr.stoneBig;

	for (int i = 0; i < ILE; i++){
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(wndow.getSize().y / 12);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(float(wndow.getSize().y / 3),
			float(wndow.getSize().y / 2.5 + i * wndow.getSize().y / 6.4));
	}

	spr.tankIco.setScale(float(map.pr.scale * 1.5), float(map.pr.scale * 1.5));

	icon = GameState::SinglePlayerGame;

	while (state == GameState::Menu){
		FPSclock.StopClock();
		eventsMenu();

		//change the color to red 
		for (int i = 0; i < ILE; i++){
			if (i == int(icon) - 1){
				tekst[i].setFillColor(sf::Color::Red);
				spr.tankIco.setPosition(tekst[i].getPosition());
				spr.tankIco.move(float(wndow.getSize().x) / float(-20.0), 0);
			}
			// put the color to be white 
			else tekst[i].setFillColor(sf::Color::White);
		}
		wndow.clear();
		// build the menu stone
		for (int y = 0; y < 15; y++){
			for (int x = 0; x < map.pr.widthInBlocks / 2; x++){
				if (x == 0 || y == 0 || x == map.pr.widthInBlocks / 2 - 1 || y == 14){
					menuStone.setScale(map.pr.scale, map.pr.scale); 
					menuStone.setPosition(float(map.pr.sides + x * (map.pr.blockSize * 2)), float(map.pr.topBot + y * (map.pr.blockSize * 2)));
					wndow.draw(menuStone);
				}
			}
		}
		spr.backGround.setPosition(float(std::round(map.pr.widthInBlocks / 8) * map.pr.blockSize + map.pr.sides), float(4 * map.pr.blockSize + map.pr.topBot));
		spr.backGround.setScale( map.pr.scale*0.8, map.pr.scale*0.8);
		wndow.draw(spr.backGround);

		spr.control.setPosition(1050, 780);
		//float(float(map.pr.widthInBlocks*30) - float(4 * map.pr.blockSize + map.pr.topBot)),float(std::round(map.pr.widthInBlocks / 8) * map.pr.blockSize + map.pr.sides)
		spr.control.setScale(map.pr.scale*1.2, map.pr.scale*1.2);
		wndow.draw(spr.control);
		wndow.draw(spr.tankIco);
		for (int i = 0; i < ILE; i++){
			wndow.draw(tekst[i]);
		}
		FPSclock.draw(wndow);
		wndow.display();
	}
}

void Game::eventsMenu(){
	sf::Event event;
	while (wndow.pollEvent(event)){
		// Press ESC or the X button in the window
		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Escape)
			state = GameState::EXIT;
		// 1 player mode (tank in the right position + enter)
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return &&
			icon == GameState::SinglePlayerGame){
			state = GameState::SinglePlayerGame;
		}
		// 2 players mode (tank in the right position + enter)
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return &&
			icon == GameState::TwoPlayerGame){
			state = GameState::TwoPlayerGame;
		}
		// EXIT mode (tank in the right position + enter)
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return &&
			icon == GameState::EXIT){
			state = GameState::EXIT;
		}
		// moving the tank icon - arrow up
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Up && int(icon) > 1){
			switch (icon){
			case GameState::TwoPlayerGame: icon = GameState::SinglePlayerGame;
				break;
			case GameState::EXIT: icon = GameState::TwoPlayerGame;
				break;
			}
		}
		// moving the tank icon - arrow down
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Down && int(icon) < 3){
			switch (icon){
			case GameState::SinglePlayerGame: icon = GameState::TwoPlayerGame;
				break;
			case GameState::TwoPlayerGame: icon = GameState::EXIT;
				break;
			}
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T){
			FPSclock.switchClock();
		}
	}
}