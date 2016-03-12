#pragma once
#include <Windows.h>

#include "single.h"
#include "sprite.h"
#include "map.h"
#include "block.h"
#include "fpsClock.h"

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
	sf::RenderWindow okno;

	GameState icon;		//potrzebne do okreœlania pozycji czo³gu w menu
	GameState state;	//obecny status manu gry (menu, single, multi etc)

	Sprite spr;			//klasa przechowuj¹ca tekstury
	Map map;			//klasa wyœwietlaj¹ca mapê

	sf::Font font;		//potrzebna czcionka
	Timer FPSclock;

	//funkcje zwi¹zane z menu
	void menu();
	void game(bool x){
		if (x == 0){
			Single single{ x, font, map, spr, okno, FPSclock };
			single.runSingle();

			state = GameState::Menu;
		}
		else{
			Single single{ x, font, map, spr, okno, FPSclock };
			single.runSingle();

			state = GameState::Menu;
		}
	}
	void eventsMenu();
public:
	Game(void) : map{ spr, okno }, FPSclock{ font }{
		std::srand(unsigned(std::time(nullptr)));
		okno.create(sf::VideoMode(1920, 1080), "Tanks by Rafal Kopczynski", sf::Style::Fullscreen);
		okno.setFramerateLimit(60);
		map.setProperties(okno);

		state = GameState::EXIT;
		if (!spr.isGood()){
			MessageBox(NULL, "Some image not found!", "ERROR", NULL);
			return;
		}
		if (!font.loadFromFile("data/joystix monospace.ttf")){
			MessageBox(NULL, "Font not found!", "ERROR", NULL);
			return;
		}
		state = GameState::Menu;
	}
};