#include "collision.h"
#include "sprite.h"
#include "map.h"

#include <iostream>

Collision::Collision(Sprite & spr, Map & map, bool player, int ID, Move move) 
	: sprite{ spr }, map{ map }, player{ player }, objID{ ID }, move{ move }{}

void Collision::checkCollision(std::list<TankPtr> & tanks, std::list<Bullet> & bullets){
	//sprawdzamy zegar ruchu, nie chcemy
	//aby czo�g za szybko zapierdziela� :P
	if (timer.getElapsedTime().asSeconds() >= speed){

		//Sprawdzamy, czy ruch w og�le zachodzi.
		if (move != Move::none){
			//Je�li tak, to wyci�gamy box'a otaczaj�cego pojazd
			//do przetestowania, czy nie najedzie na niew�a�ciwy blok
			sf::FloatRect box = spr.getGlobalBounds();

			//Sprawdzamy pozycj� czo�gu na mapie
			posMap.x = int((spr.getPosition().x - map.pr.sides) / map.pr.blockSize);
			posMap.y = int((spr.getPosition().y - map.pr.topBot) / map.pr.blockSize);

			float speed{ map.pr.blockSize / 4.f };

			//zmieniamy obrazek
			updateImage();

			bool COL{ false };

			//Kolizja z blokami wzgl�dem kierunku ruchu
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
			//sprawdzamy czy nie zachodzi kolizja z reszt� czo�g�w
			if (colWithTanks(tanks, bullets, speed)) return;

			//Je�li kolizja si� nie pojawi�a, to przesuwamy
			//w�a�ciwego spite'a pojazdu na pozycj� box'a
			//oraz nadpisujemy pozycj� g��wn�
			pos.x = box.left;
			pos.y = box.top;
			spr.setPosition(box.left, box.top);

			//resetujemy timer ruchu
			timer.restart();
		}
	}
	//Je�li kt�ry� "if" nas wywali�, to ustawiamy
	//objekt na pozycj� domy�ln�
	spr.setPosition(pos);
}