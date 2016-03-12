#pragma once
#include "tank.h"
#include "map.h"

class Player : public Tank{
public:
	//konstruktor
	Player(std::list<Explosion> & explosions, std::list<Bullet> & bullets, Sprite & sprite, Map & map, bool isPlayer = true, int ID = 0, Move move = Move::up)
		: Tank{ explosions, bullets, sprite, map, isPlayer, ID, move }
	{
		speed = { 0.033f };

		spr = sprite.tankYellow;

		pos.x = float(map.pr.sides + map.pr.blockSize * 10);
		pos.y = float(map.pr.topBot + map.pr.blockSize * 26);

		spr.setPosition(pos);
		spr.setScale(map.pr.scale, map.pr.scale);

		updateImage();
	}
	virtual ~Player(void){}

	//metoda ruchu postaci
	void checkMove(){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
			lastMove = move = Move::up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
			lastMove = move = Move::down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
			lastMove = move = Move::left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
			lastMove = move = Move::right;
		}
		else{
			if (move != Move::none) lastMove = move;
			move = Move::none;
		}
		//if (canShoot && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
		//	bullets.emplace_back(sprite, map, pos, objID, lastMove, player);
		//	canShoot = { false };
		//}
	}
};