#pragma once
#include <SFML\Graphics.hpp>

class Sprite{
private:
	//bloki
	sf::Texture airTx;
	sf::Texture brickTx;
	sf::Texture stoneTx;
	sf::Texture stoneBigTx;
	sf::Texture greenTx;
	sf::Texture waterTx;
	//sf::Texture roadTx;

	//rzeczy z menu

	sf::Texture backGroundTx;	//T³o za tytu³em w menu :>

	//obrazki czo³gów

	sf::Texture tankGreenTx;
	sf::Texture tankYellowTx;
	sf::Texture tankRedTx;
	sf::Texture tankGreyTx;

	//pocisk
	sf::Texture bulletTx;

	//kurak
	sf::Texture kurakTx;
	sf::Texture kurakDeadTx;

	//wybuch
	sf::Texture wybuchTx;

	bool load;
public:
	//bloki

	sf::Sprite air;
	sf::Sprite brick;
	sf::Sprite stone;
	sf::Sprite stoneBig;
	sf::Sprite green;
	sf::Sprite water;
	sf::Sprite road;

	//rzeczy z menu

	sf::Sprite tankIco;
	sf::Sprite backGround;

	//obrazki czo³gów

	sf::Sprite tankGreen;
	sf::Sprite tankYellow;
	sf::Sprite tankRed;
	sf::Sprite tankGrey;

	//pocisk
	sf::Sprite bullet;

	//kurak
	sf::Sprite kurak;
	sf::Sprite kurakDead;

	//wybuch
	sf::Sprite wybuch;

	bool isGood(){ return load; }
	Sprite(void);
};