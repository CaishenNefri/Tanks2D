#include "map.h"

void Block::setImg(Sprite & spr){
	switch (type){
	case Block::Type::air:			img = spr.air; break;
	case Block::Type::brick:		img = spr.brick; break;
	case Block::Type::stone:		img = spr.stone; break;
	case Block::Type::green:		img = spr.green; break;
	case Block::Type::water:		img = spr.water;  break;
	case Block::Type::road:			img = spr.road; break;
	case Block::Type::endMap:		img = spr.stone; break;
	case Block::Type::kurak:		img = spr.kurak; break;
	case Block::Type::kurakDEAD:	img = spr.kurakDead; break;
	}
}
void Block::setMoveMode(){
	switch (type){
	case Block::Type::air:		move = Move::moveAble; break;
	case Block::Type::green:	move = Move::moveAble; break;
	case Block::Type::water:	move = Move::water; break;
	case Block::Type::road:		move = Move::moveAble; break;
	case Block::Type::endMap:	move = Move::endMap; break;
	default: move = Move::notMoveAble; break;
	}
}
void Block::shotBlock(Sprite & spr){
	if (hardness > 0){
		hardness--;
	}
	else{
		type = Type::air;
		setImg(spr);
	}
}
void Block::setHardness(){
	switch (type){
	case Block::Type::brick: hardness = { 1 }; break;
	case Block::Type::stone: hardness = { 3 }; break;
	case Block::Type::kurak: hardness = { 0 }; break;
	}
}
void Block::shotKurak(Map & map){
	sf::Vector2f position;
	for (int x = 0; x < 2; x++){
		for (int y = 0; y < 2; y++){
			position = map.tab[26 + y][14 + x].img.getPosition();
			map.tab[26 + y][14 + x].img = map.spr.kurakDead;
			map.tab[26 + y][14 + x].img.setTextureRect(sf::IntRect(x * 50,
				y * 50, 100, 100));
			map.tab[26 + y][14 + x].img.setPosition(position);
			map.tab[26 + y][14 + x].img.setScale(map.pr.scale, map.pr.scale);
			map.tab[26 + y][14 + x].move = Block::Move::notMoveAble;
			map.tab[26 + y][14 + x].type = Block::Type::kurakDEAD;
			map.tab[26 + y][14 + x].setHardness();
		}
	}
}