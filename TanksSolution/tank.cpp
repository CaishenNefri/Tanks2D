#include "tank.h"
#include "sprite.h"
#include "map.h"
#include "explosion.h"

Tank::Tank(std::list<Explosion> & explosions, std::list<Bullet> & bullets, Sprite & sprite, Map & map, bool isPlayer, int ID, Move move)
	: Collision{ sprite, map, isPlayer, ID, move }, bullets{ bullets }, explosions{ explosions }
{
	speed = { 0.040f };

	spr = sprite.tankGreen;

	pos = map.tab[26][10].img.getPosition();

	spr.setPosition(pos);
	spr.setScale(map.pr.scale, map.pr.scale);

	updateImage();
}
Tank::~Tank(void){
	if (exist == false) explosions.push_back(Explosion{ map, *this });
}

void Tank::draw(sf::RenderTarget & okno, sf::RenderStates st) const{
	okno.draw(spr);
}
bool Tank::collision(Pos posMap, sf::FloatRect & box){
	Block collisionBlock = map.tab[posMap.y][posMap.x];

	if (box.intersects(collisionBlock.img.getGlobalBounds())){
		if (collisionBlock.move == Block::Move::notMoveAble ||
			collisionBlock.move == Block::Move::water ||
			collisionBlock.move == Block::Move::endMap){
			spr.setPosition(pos);
			move = Move::none;
			return 1;
		}
	}
	return 0;
}

bool Tank::colWithTanks(std::list<TankPtr> & tanks, std::list<Bullet> & bullets, float speed){
	sf::FloatRect box = this->spr.getGlobalBounds();

	switch (this->move){
	case Tank::Move::left: box.left -= speed;
		break;
	case Tank::Move::right: box.left += speed;
		break;
	case Tank::Move::up: box.top -= speed;
		break;
	case Tank::Move::down: box.top += speed;
		break;
	}

	for (auto & tank : tanks){
		if (this->objID != tank->objID){
			if (box.intersects(tank->spr.getGlobalBounds())){
				this->spr.setPosition(pos);
				this->move = Move::none;
				return 1;
			}
		}
	}
	return 0;
}


/*
bool Tank::spawnCollision(std::list<TankPtr> & tanks){
	sf::FloatRect box = this->spr.getGlobalBounds();

	for (auto & tank : tanks){
		if (this->objID != tank->objID){
			if (box.intersects(tank->spr.getGlobalBounds())){
				this->spr.setPosition(pos);
				move = Move::none;
				return 1;
			}
		}
	}
	return 0;
}
*/

void Tank::updateImage(){
	switch (move){
	case Collision::Move::left:
		spr.setTextureRect(sf::IntRect(0, 0, 100, 100));
		break;
	case Collision::Move::right:
		spr.setTextureRect(sf::IntRect(100, 0, 100, 100));
		break;
	case Collision::Move::up:
		spr.setTextureRect(sf::IntRect(200, 0, 100, 100));
		break;
	case Collision::Move::down:
		spr.setTextureRect(sf::IntRect(300, 0, 100, 100));
		break;
	}
}
bool Tank::spawnCollision(std::list<TankPtr> & tanks){
	sf::FloatRect box = this->spr.getGlobalBounds();

	for (auto & tank : tanks){
		if (this->objID != tank->objID){
			if (box.intersects(tank->spr.getGlobalBounds())){
				this->spr.setPosition(pos);
				move = Move::none;
				return 1;
			}
		}
	}
	return 0;
}