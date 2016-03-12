#pragma once
#include "sprite.h"
#include "map.h"
#include "fpsClock.h"
//#include <list>

//#include "level.h"
//#include "player.h"
//#include "enemy.h"
//#include "tank.h"
//#include "bullet.h"

class Single{
public:
	void runSingle();
	Single(bool, sf::Font &, Map &, Sprite &, sf::RenderWindow &, Timer &);
private:
	bool gameType;
	sf::Font & font;	//czcionka
	Map & map;			//referencja do mapy
	Sprite & spr;				//referencja do klasy trzymaj¹cej obrazki
	sf::RenderWindow & okno;	//referencja do okna
	Timer & FPSclock;
	
	void clearDeathObjects();
};