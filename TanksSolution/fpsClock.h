#pragma once
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>

class Timer{
private:
	sf::Font & font;
	sf::Text txt;
	sf::Clock time;

	int actualFPS, countFPS;
	bool clockON{ true };
public:
	void switchClock(){ clockON = !clockON; }
	Timer(sf::Font & font) : font{ font }, actualFPS{}, countFPS{}{}

	void draw(sf::RenderWindow & okno){
		if (clockON){
			if (time.getElapsedTime().asSeconds() >= 1){
				actualFPS = countFPS;
				countFPS = { 0 };
				time.restart();
			}
			else ++countFPS;
			txt.setFont(font);
			txt.setCharacterSize(okno.getSize().y / 24);
			txt.setColor(sf::Color::Red);
			txt.setString("FPS: " + std::to_string(actualFPS));
			txt.setPosition(float(okno.getSize().x - txt.getGlobalBounds().width), float(0.0));

			okno.draw(txt);
		}
	}
};