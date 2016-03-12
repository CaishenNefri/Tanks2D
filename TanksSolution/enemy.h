#pragma once
#include "tank.h"
#include "map.h"

class Enemy : public Tank{
public:
	//Status ruchu czo³gu w nastêpuj¹cym schemacie:
	// 1.	Najpierw ruch w dó³ (na okreœlon¹ d³ugoœæ)
	// 2.	Jeœli siê zatrzyma lub przejdzie okreœlon¹ d³ugoœæ to punkt 3
	// 3.	Wybiera ruch lewo
	// 4.	Jeœli nie mo¿ê siê ruszyæ to w prawo
	// 4.	...
	enum class MoveState { down, left, right, up };

	//konstruktor
	Enemy(std::list<Explosion> & explosions, std::list<Bullet> & bullets, Sprite & sprite, Map & map, int ID, Level::NewTankPos tankPos, bool isPlayer = false, Move move = Move::down)
		: Tank{ explosions, bullets, sprite, map, isPlayer, ID, move }
	{
		speed = { 0.040f };

		if (std::rand() % 2) spr = sprite.tankGrey;
		else spr = sprite.tankRed;

		//wybieramy pozycjê
		switch (tankPos){
		case Level::NewTankPos::left:{
			pos.x = float(map.pr.sides + map.pr.blockSize * 2);
			pos.y = float(map.pr.topBot + map.pr.blockSize);
		} break;
		case Level::NewTankPos::mid:{
			pos.x = float(map.pr.sides + map.pr.blockSize * 14);
			pos.y = float(map.pr.topBot + map.pr.blockSize);
		} break;
		case Level::NewTankPos::right:{
			pos.x = float(map.pr.sides + map.pr.blockSize * 26);
			pos.y = float(map.pr.topBot + map.pr.blockSize);
		} break;
		}

		spr.setPosition(pos.x, pos.y);
		spr.setScale(map.pr.scale, map.pr.scale);

		updateImage();

		lastMove = move;
	}
	//destruktor
	virtual ~Enemy(void){}

	//metoda ruchu postaci
	void checkMove(){
		if (move == Move::none){
			lastMove = move = Move(rand() % 4);
		}	
		if (canShoot && std::rand() % 100 == false){
			bullets.emplace_back(sprite, map, pos, objID, lastMove, player);
			canShoot = { false };
		}
	}
};