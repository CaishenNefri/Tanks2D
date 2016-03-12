#include "sprite.h"

Sprite::Sprite(void){
	load = { false };
	if (!airTx.loadFromFile("data/blocks/airTx.gif")) return;
	if (!brickTx.loadFromFile("data/blocks/brickTx.gif")) return;
	if (!stoneTx.loadFromFile("data/blocks/stoneTx.gif")) return;
	if (!stoneBigTx.loadFromFile("data/blocks/stoneBigTx.gif")) return;
	if (!greenTx.loadFromFile("data/blocks/greenTx.gif")) return;
	if (!waterTx.loadFromFile("data/blocks/waterTx.gif")) return;
	//if (!roadTx.loadFromFile("data/roadTx_beta.jpg")) return;

	//rzeczy z menu
	if (!backGroundTx.loadFromFile("data/backGroundTx.gif")) return;

	//obrazki czo�g�w
	if (!tankGreenTx.loadFromFile("data/tanks/tankGreenTx.gif")) return;
	if (!tankYellowTx.loadFromFile("data/tanks/tankYellowTx.gif")) return;
	if (!tankRedTx.loadFromFile("data/tanks/tankRedTx.gif")) return;
	if (!tankGreyTx.loadFromFile("data/tanks/tankGreyTx.gif")) return;

	//pocisk
	if (!bulletTx.loadFromFile("data/bulletTx.gif")) return;

	//kurak
	if (!kurakTx.loadFromFile("data/kurak/kurakTx.gif")) return;
	if (!kurakDeadTx.loadFromFile("data/kurak/kurakDeadTx.gif")) return;

	//wybuch
	if (!wybuchTx.loadFromFile("data/wybuchTx.gif")) return;

	load = { true };

	//�adowanie tekstur do sprite'�w
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

	//czo�gi
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