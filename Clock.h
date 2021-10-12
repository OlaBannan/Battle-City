#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <string>
 // #define SFML_NO_DEPRECATED_WARNINGS

class Timer {
private:
	sf::Font & font;
	sf::Text txt;
	sf::Clock time;

	int actualFPS, countFPS;
	bool clockON{ true };
public:
	void switchClock() { clockON = !clockON; }
	Timer(sf::Font & font) : font{ font }, actualFPS{}, countFPS{}{time.restart(); }
	void restart() { time.restart(); };
	void StopClock() { if (clockON) switchClock(); };

	void draw(sf::RenderWindow & wndow) {
		if (clockON) {
		
			countFPS = int(time.getElapsedTime().asSeconds());
			txt.setFont( font);
			txt.setCharacterSize(wndow.getSize().y / 24);
			txt.setFillColor(sf::Color::Red);
			txt.setString("Clock: " + std::to_string(int(countFPS)));
			txt.setPosition(float(wndow.getSize().x - txt.getGlobalBounds().width), float(0.0));

			wndow.draw(txt);
		}
	}
};