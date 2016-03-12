#include "collision.h"
#include "sprite.h"
#include "map.h"

#include <iostream>

Collision::Collision(Sprite & spr, Map & map, bool player, int ID, Move move) 
	: sprite{ spr }, map{ map }, player{ player }, objID{ ID }, move{ move }{}

void Collision::checkCollision(std::list<TankPtr> & tanks, std::list<Bullet> & bullets){
	//sprawdzamy zegar ruchu, nie chcemy
	//aby czo³g za szybko zapierdziela³ :P
	if (timer.getElapsedTime().asSeconds() >= speed){

		//Sprawdzamy, czy ruch w ogóle zachodzi.
		if (move != Move::none){
			//Jeœli tak, to wyci¹gamy box'a otaczaj¹cego pojazd
			//do przetestowania, czy nie najedzie na niew³aœciwy blok
			sf::FloatRect box = spr.getGlobalBounds();

			//Sprawdzamy pozycjê czo³gu na mapie
			posMap.x = int((spr.getPosition().x - map.pr.sides) / map.pr.blockSize);
			posMap.y = int((spr.getPosition().y - map.pr.topBot) / map.pr.blockSize);

			float speed{ map.pr.blockSize / 4.f };

			//zmieniamy obrazek
			updateImage();

			bool COL{ false };

			//Kolizja z blokami wzglêdem kierunku ruchu
			switch (move){
			case Collision::Move::left:{
				box.left -= speed;
				posMap.x--;
				if (collision(posMap, box)) COL = { true };
				posMap.y++;
				if (collision(posMap, box)) COL = { true };
				posMap.y++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
			} break;
			case Collision::Move::right:{
				box.left += speed;
				posMap.x += 2;
				if (collision(posMap, box)) COL = { true };
				posMap.y++;
				if (collision(posMap, box)) COL = { true };
				posMap.y++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
			} break;
			case Collision::Move::up:{
				box.top -= speed;
				posMap.y--;
				if (collision(posMap, box)) COL = { true };
				posMap.x++;
				if (collision(posMap, box)) COL = { true };
				posMap.x++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
			} break;
			case Collision::Move::down:{
				box.top += speed;
				posMap.y += 2;
				if (collision(posMap, box)) COL = { true };
				posMap.x++;
				if (collision(posMap, box)) COL = { true };
				posMap.x++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
			} break;
			}
			//sprawdzamy czy nie zachodzi kolizja z reszt¹ czo³gów
			if (colWithTanks(tanks, bullets, speed)) return;

			//Jeœli kolizja siê nie pojawi³a, to przesuwamy
			//w³aœciwego spite'a pojazdu na pozycjê box'a
			//oraz nadpisujemy pozycjê g³ówn¹
			pos.x = box.left;
			pos.y = box.top;
			spr.setPosition(box.left, box.top);

			//resetujemy timer ruchu
			timer.restart();
		}
	}
	//Jeœli któryœ "if" nas wywali³, to ustawiamy
	//objekt na pozycjê domyœln¹
	spr.setPosition(pos);
}