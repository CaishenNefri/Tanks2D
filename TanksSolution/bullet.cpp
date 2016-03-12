#include "bullet.h"
#include "map.h"
#include "sound.h"

extern Sound sound;

Bullet::Bullet(Sprite & spr, Map & map, sf::Vector2f tankPos, int ID, Move move, bool isPlayer)
: Collision{ spr, map, isPlayer, ID, move }
{
	speed = { 0.015f };

	this->spr = sprite.bullet;

	updateImage();

	setStartPos(tankPos);
}
void Bullet::draw(sf::RenderTarget & okno, sf::RenderStates st) const{
	okno.draw(spr);
}
bool Bullet::collision(Pos posMap, sf::FloatRect & box){
	Block collisionBlock = map.tab[posMap.y][posMap.x];
	if (box.intersects(collisionBlock.img.getGlobalBounds())){
		if (collisionBlock.move == Block::Move::notMoveAble){
			if (collisionBlock.type == Block::Type::kurakDEAD){
				spr.setPosition(pos);
				exist = { false };
				move = Move::none;
				return 1;
			}
			else if (collisionBlock.type == Block::Type::kurak){
				sound.Sounds["strza³Blok"].play();
				map.tab[posMap.y][posMap.x].shotKurak(map);
				spr.setPosition(pos);
				exist = { false };
				move = Move::none;
				return 1;
			}
			else{
				sound.Sounds["strza³Blok"].play();
				map.tab[posMap.y][posMap.x].shotBlock(sprite);
				spr.setPosition(pos);
				exist = { false };
				move = Move::none;
				return 1;
			}
		}
		else if (collisionBlock.move == Block::Move::endMap){
			sound.Sounds["strza³Blok"].play();
			spr.setPosition(pos);
			exist = { false };
			move = Move::none;
			return 1;
		}
	}
	return 0;
}
bool Bullet::colWithTanks(std::list<TankPtr> & tanks, std::list<Bullet> & bullets, float speed)
{
	sf::FloatRect box = this->spr.getGlobalBounds();

	switch (this->move){
	case Bullet::Move::left: box.left -= speed;
		break;
	case Bullet::Move::right: box.left += speed;
		break;
	case Bullet::Move::up: box.top -= speed;
		break;
	case Bullet::Move::down: box.top += speed;
		break;
	}
	//niszczenie czo³gów
	for (auto & tank : tanks){
		if (box.intersects(tank->spr.getGlobalBounds())){
			if (this->player != tank->player){
				this->spr.setPosition(pos);
				this->exist = { false };
				tank->exist = { false };
				return 1;
			}
			else if (this->objID != tank->objID){
				this->spr.setPosition(pos);
				this->exist = { false };
				return 1;
			}
			else{
				this->spr.setPosition(box.left, box.top);
				return 1;
			}
		}
	}
	return colWithBullets(bullets, box);
}
void Bullet::setStartPos(sf::Vector2f tankPos){
	this->spr.setPosition(tankPos.x, tankPos.y);
	this->spr.scale(map.pr.scale, map.pr.scale);

	//sprawdzam rozmiar pocisku (sprajta) i wyliczam jego po³owê
	float picWidth = float(spr.getGlobalBounds().height / 2.0);

	switch (move){
	case Collision::Move::left:
		tankPos.y += map.pr.blockSize - picWidth;
		break;
	case Collision::Move::right:
		tankPos.x += map.pr.blockSize - picWidth;
		tankPos.y += map.pr.blockSize - picWidth;
		break;
	case Collision::Move::up:
		tankPos.x += map.pr.blockSize - picWidth;
		break;
	case Collision::Move::down:
		tankPos.x += map.pr.blockSize - picWidth;
		tankPos.y += map.pr.blockSize - picWidth;
		break;
	}
	pos = tankPos;
	this->spr.setPosition(pos.x, pos.y);
}
bool Bullet::colWithBullets(std::list<Bullet> & bullets, sf::FloatRect & box){
	for (auto & bullet = bullets.begin(); bullet != bullets.end(); bullet++){
		if (box.intersects(bullet->spr.getGlobalBounds())){
			if (this->player != bullet->player){
				this->spr.setPosition(pos);
				bullet->exist = exist = { false };
				return 1;
			}
			else if (this->objID != bullet->objID){
				this->spr.setPosition(pos);
				this->exist = { false };
				return 1;
			}
			else{
				this->spr.setPosition(box.left, box.top);
				return 1;
			}
		}
	}
	return 0;
}
void Bullet::updateImage(){
	switch (move){
	case Collision::Move::left:
		this->spr.setTextureRect(sf::IntRect(0, 0, 40, 40));
		break;
	case Collision::Move::right:
		this->spr.setTextureRect(sf::IntRect(40, 0, 40, 40));
		break;
	case Collision::Move::up:
		this->spr.setTextureRect(sf::IntRect(80, 0, 40, 40));
		break;
	case Collision::Move::down:
		this->spr.setTextureRect(sf::IntRect(120, 0, 40, 40));
		break;
	}
}
void Bullet::checkCollision(std::list<TankPtr> & tanks, std::list<Bullet> & bullets){
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
			case Collision::Move::left:
				box.left -= speed;
				posMap.x--;
				if (collision(posMap, box)) COL = { true };
				posMap.y++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
				break;
			case Collision::Move::right:
				box.left += speed;
				posMap.x += 1;
				if (collision(posMap, box)) COL = { true };
				posMap.y++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
				break;
			case Collision::Move::up:
				box.top -= speed;
				posMap.y--;
				if (collision(posMap, box)) COL = { true };
				posMap.x++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
				break;
			case Collision::Move::down:
				box.top += speed;
				posMap.y += 1;
				if (collision(posMap, box)) COL = { true };
				posMap.x++;
				if (collision(posMap, box)) COL = { true };
				if (COL) return;
				break;
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