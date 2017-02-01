#include "sprite.h"

Sprite::Sprite(void){
	load = { false };
	if (!airTx.loadFromFile("data/blocks/airTx.png")) return;
	if (!brickTx.loadFromFile("data/blocks/brickTx.gif")) return;
	if (!stoneTx.loadFromFile("data/blocks/stoneTx.gif")) return;
	if (!stoneBigTx.loadFromFile("data/blocks/stoneBigTx.gif")) return;
	if (!greenTx.loadFromFile("data/blocks/greenTx.png")) return;
	if (!waterTx.loadFromFile("data/blocks/waterTx.gif")) return;
	//if (!roadTx.loadFromFile("data/roadTx_beta.jpg")) return;

	//rzeczy z menu
	if (!backGroundTx.loadFromFile("data/backGroundTx.gif")) return;

	//obrazki czo³gów
	if (!tankGreenTx.loadFromFile("data/tanks/tankGreenTx.png")) return;
	if (!tankYellowTx.loadFromFile("data/tanks/tankYellowTx.png")) return;
	if (!tankRedTx.loadFromFile("data/tanks/tankRedTx.png")) return;
	if (!tankGreyTx.loadFromFile("data/tanks/tankGreyTx.png")) return;

	//pocisk
	if (!bulletTx.loadFromFile("data/bulletTx.png")) return;

	//kurak
	if (!kurakTx.loadFromFile("data/kurak/kurakTx.png")) return;
	if (!kurakDeadTx.loadFromFile("data/kurak/kurakDeadTx.png")) return;

	//wybuch
	if (!wybuchTx.loadFromFile("data/wybuchTx.gif")) return;

	load = { true };

	//³adowanie tekstur do sprite'ów
	//bloki
	air.setTexture(airTx);
	brick.setTexture(brickTx);
	stone.setTexture(stoneTx);
	stoneBig.setTexture(stoneBigTx);
	green.setTexture(greenTx);
	water.setTexture(waterTx);
	//road.setTexture(roadTx);

	//manu
	backGround.setTexture(backGroundTx);
	tankIco.setTexture(tankYellowTx);
	tankIco.setTextureRect(sf::IntRect(200, 0, 100, 100));
	tankIco.rotate(90);

	//czo³gi
	tankGreen.setTexture(tankGreenTx);
	tankYellow.setTexture(tankYellowTx);
	tankRed.setTexture(tankRedTx);
	tankGrey.setTexture(tankGreyTx);

	//pocisk
	bullet.setTexture(bulletTx);

	//kurak
	kurak.setTexture(kurakTx);
	kurakDead.setTexture(kurakDeadTx);

	//wybuch
	wybuch.setTexture(wybuchTx);
}