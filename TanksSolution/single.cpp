#include "single.h"
#include "sound.h"

extern Sound sound;

Single::Single(bool x, sf::Font & font, Map & map, Sprite & spr, sf::RenderWindow & okno, Timer & FPSclock)
	: font{ font }, map{ map }, spr{ spr }, okno{ okno }, FPSclock{ FPSclock }
{
	gameType = x;
}
void Single::runSingle(){
	map.initiateGame(gameType);
	while (map.gameGood()){
		map.loadMap();
		while (map.checkGameStatus()){
			sound.updateSound(map.lvl.tanks);

			map.events(FPSclock);

			//dodawanie czo³gów
			map.addPlayer1Tank();
			if(gameType) map.addPlayer2Tank();
			map.addEnemyTank();

			//kolizje
			for (auto & tank : map.lvl.tanks){
				tank->checkMove();
				tank->checkCollision(map.lvl.tanks, map.lvl.bullets);
			}
			for (auto & bullet : map.lvl.bullets){
				bullet.checkCollision(map.lvl.tanks, map.lvl.bullets);
			}

			//usuwanie "trupów"
			clearDeathObjects();

			//rysowanie
			okno.clear();
			for (auto & tank : map.lvl.tanks){
				okno.draw(*tank);
			}
			okno.draw(map);
			for (auto & bullet : map.lvl.bullets){
				okno.draw(bullet);
			}
			for (auto & x : map.lvl.explosions){
				okno.draw(x);
			}

			FPSclock.draw(okno);
			okno.display();
		}
	}
	sound.stopAll();
	map.endGame();
}
void Single::clearDeathObjects(){	
	//przywracanie mo¿liwoœci strza³ czo³gom
	for (auto bullet : map.lvl.bullets){
		if (bullet.exist == false){
			for (auto & tank : map.lvl.tanks){
				if (bullet.objID == tank->objID){
					tank->canShoot = { true };
					break;
				}
			}
		}
	}	
	//pozbywanie siê pocisków
BACK:
	for (auto & i = map.lvl.bullets.begin(); i != map.lvl.bullets.end(); i++){
		if (i->exist == false){
			map.lvl.bullets.erase(i);
			goto BACK;
		}
	}
	//map.lvl.bullets.erase(std::remove_if(map.lvl.bullets.begin(), map.lvl.bullets.end(),
	//	[](const Bullet & x)->bool{return x.exist == false; }), map.lvl.bullets.end());

	map.lvl.tanks.erase(std::remove_if(map.lvl.tanks.begin(), map.lvl.tanks.end(),
		[&](const TankPtr & x)->bool{return x->exist == false; }), map.lvl.tanks.end());

	map.lvl.explosions.erase(std::remove_if(map.lvl.explosions.begin(), map.lvl.explosions.end(),
		[&](Explosion & x)->bool{return x.stillExist() == false; }), map.lvl.explosions.end());
}