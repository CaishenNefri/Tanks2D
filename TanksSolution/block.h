#pragma once
#include "sprite.h"

class Map;

class Block{
public:
	enum class Type{ air, brick, stone, green, water, road, endMap, kurak, kurakDEAD } type;
	enum class Move{ moveAble, notMoveAble, water, endMap } move;
	enum class Pos{ pos1, pos2, pos3, pos4 } pos;

	sf::Sprite img;
	bool hide{ false };

	void setImg(Sprite & spr);
	void setHardness();
	void setMoveMode();
	void shotBlock(Sprite & spr);
	void shotKurak(Map & map);
private:
	int hardness{ 0 };
};