#include "map.h"
#include "player.h"
#include "player2.h"
#include "enemy.h"
#include <fstream>
#include "sound.h"

extern Sound sound;

Map::Map(Sprite & spr, sf::RenderWindow & okno) : spr{ spr }, okno{ okno }{}

void Map::loadMap(){
	int type, sett;
	std::fstream Plik("data/levels/level1.txt", std::ios::in);

	Plik >> lvl.enemyTanks;

	for (int y = 0; y < blockSIZE / 2; y++){
		for (int x = 0, X = x * 2, Y = y * 2; x < blockSIZE / 2; x++, X = x * 2, Y = y * 2){
			Plik >> type >> sett;
			tab[Y][X].pos = Block::Pos::pos1;
			tab[Y][X + 1].pos = Block::Pos::pos2;
			tab[Y + 1][X + 1].pos = Block::Pos::pos3;
			tab[Y + 1][X].pos = Block::Pos::pos4;

			switch (Map::Sett(sett)){
			case Map::Sett::left:
				tab[Y][X].type = tab[Y + 1][X].type = Block::Type(type);
				tab[Y][X + 1].type = tab[Y + 1][X + 1].type = Block::Type::air;
				break;
			case Map::Sett::up:
				tab[Y][X].type = tab[Y][X + 1].type = Block::Type(type);
				tab[Y + 1][X].type = tab[Y + 1][X + 1].type = Block::Type::air;
				break;
			case Map::Sett::right:
				tab[Y][X + 1].type = tab[Y + 1][X + 1].type = Block::Type(type);
				tab[Y][X].type = tab[Y + 1][X].type = Block::Type::air;
				break;
			case Map::Sett::down:
				tab[Y + 1][X].type = tab[Y + 1][X + 1].type = Block::Type(type);
				tab[Y][X].type = tab[Y][X + 1].type = Block::Type::air;
				break;
			case Map::Sett::corner1:
				tab[Y][X].type = Block::Type(type);
				tab[Y][X + 1].type = tab[Y + 1][X].type = tab[Y + 1][X + 1].type = Block::Type::air;
				break;
			case Map::Sett::corner2:
				tab[Y][X + 1].type = Block::Type(type);
				tab[Y][X].type = tab[Y + 1][X].type = tab[Y + 1][X + 1].type = Block::Type::air;
				break;
			case Map::Sett::corner3:
				tab[Y + 1][X + 1].type = Block::Type(type);
				tab[Y][X + 1].type = tab[Y + 1][X].type = tab[Y][X].type = Block::Type::air;
				break;
			case Map::Sett::corner4:
				tab[Y + 1][X].type = Block::Type(type);
				tab[Y][X + 1].type = tab[Y][X].type = tab[Y + 1][X + 1].type = Block::Type::air;
				break;
			case Map::Sett::cornerBig1:
				tab[Y + 1][X + 1].type = Block::Type::air;
				tab[Y][X + 1].type = tab[Y + 1][X].type = tab[Y][X].type = Block::Type(type);
				break;
			case Map::Sett::cornerBig2:
				tab[Y + 1][X].type = Block::Type::air;
				tab[Y][X + 1].type = tab[Y][X].type = tab[Y + 1][X + 1].type = Block::Type(type);
				break;
			case Map::Sett::cornerBig3:
				tab[Y][X].type = Block::Type::air;
				tab[Y][X + 1].type = tab[Y + 1][X].type = tab[Y + 1][X + 1].type = Block::Type(type);
				break;
			case Map::Sett::cornerBig4:
				tab[Y][X + 1].type = Block::Type::air;
				tab[Y][X].type = tab[Y + 1][X].type = tab[Y + 1][X + 1].type = Block::Type(type);
				break;
			case Map::Sett::full:
				tab[Y][X].type = tab[Y + 1][X].type = Block::Type(type);
				tab[Y][X + 1].type = tab[Y + 1][X + 1].type = Block::Type(type);
				break;
			}
		}
	}
	Plik.close();
	setSpritesProperties();
	setKurak();
}
void Map::events(Timer & FPSclock){
	sf::Event event;
	while (okno.pollEvent(event)){
		if (event.type == sf::Event::Closed) exit(1);
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
			state = GameState::exit;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T){
			FPSclock.switchClock();
		}
		//strzelanie gracza 1
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
			for (auto & tank : lvl.tanks){
				if (tank->objID == 0){
					if (tank->canShoot && tank->readyToShoot){
						tank->canShoot = tank->readyToShoot = { false };
						lvl.bullets.emplace_back(spr, *this, tank->pos, tank->objID, tank->lastMove, tank->player);
						sound.Sounds["strza³"].play();
						break;
					}
				}
			}
		}
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space){
			for (auto & tank : lvl.tanks){
				if (tank->objID == 0){
					if (!tank->readyToShoot){
						tank->readyToShoot = { true };
						break;
					}
				}
			}
		}
		//strzelanie gracza 2
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
			for (auto & tank : lvl.tanks){
				if (tank->objID == 1){
					if (tank->canShoot && tank->readyToShoot){
						tank->canShoot = tank->readyToShoot = { false };
						lvl.bullets.emplace_back(spr, *this, tank->pos, tank->objID, tank->lastMove, tank->player);
						sound.Sounds["strza³"].play();
						break;
					}
				}
			}
		}
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return){
			for (auto & tank : lvl.tanks){
				if (tank->objID == 1){
					if (!tank->readyToShoot){
						tank->readyToShoot = { true };
						break;
					}
				}
			}
		}
	}
}
bool Map::gameGood(){
	switch (state){
	case Map::GameState::game:		return 1;
	case Map::GameState::nextLevel: nextLevel();	return 1;
	case Map::GameState::gameOver:	gameOver();		return 0;
	case Map::GameState::exit:		return 0;
	}
}
bool Map::checkGameStatus(){
	if (lvl.playerTanks == 0){
		if (std::count_if(lvl.tanks.begin(), lvl.tanks.end(),
			[&](const TankPtr & x)->bool{return x->player; }) == 0){
			state = GameState::gameOver;
			return 0;
		}
	}
	if (lvl.enemyTanks == 0){
		if (std::count_if(lvl.tanks.begin(), lvl.tanks.end(),
			[&](const TankPtr & x)->bool{return x->player == false; }) == 0){
			state = GameState::nextLevel;
			return 0;
		}
	}
	if (checkKurakIsLive() == false){
		state = GameState::gameOver;
		return 0;
	}
	if (state == GameState::exit) return 0;
	return 1;
}
void Map::addPlayer1Tank(){
	//czo³g gracza 1
	if (lvl.playerTanks > 0){
		bool kakauko{ false };
		for (auto & tank : lvl.tanks){
			if (tank->exist == true && tank->objID == 0){
				kakauko = { true };
				break;
			}
		}
		if (!kakauko){
			if (lvl.timerPlayer1.getElapsedTime().asSeconds() >= 2.f){

				lvl.tanks.emplace_front(new Player{ lvl.explosions, lvl.bullets, spr, *this });
				if (lvl.tanks.back()->spawnCollision(lvl.tanks)){
					lvl.tanks.pop_back();
				}
				else{
					lvl.playerTanks--;
					lvl.timerPlayer1.restart();
				}
			}
		}
	}
}
void Map::addPlayer2Tank(){
	//czo³g gracza 2
	if (lvl.playerTanks > 0){
		bool kakauko{ false };
		for (auto & tank : lvl.tanks){
			if (tank->exist == true && tank->objID == 1){
				kakauko = { true };
				break;
			}
		}
		if (!kakauko){
			if (lvl.timerPlayer2.getElapsedTime().asSeconds() >= 2.f){

				lvl.tanks.emplace_front(new Player2{ lvl.explosions, lvl.bullets, spr, *this });
				if (lvl.tanks.back()->spawnCollision(lvl.tanks)){
					lvl.tanks.pop_back();
				}
				else{
					lvl.playerTanks--;
					lvl.timerPlayer2.restart();
				}
			}
		}
	}
}
void Map::addEnemyTank(){
	//sprawdzamy, czy jeszcze mamy jakieœ czo³gi
	if (lvl.enemyTanks > 0 && lvl.tanks.size() - std::count_if(lvl.tanks.begin(), lvl.tanks.end(),
		[&](const TankPtr & x)->bool{return x->player; }) < 5){

		//sprawdzamy czy ju¿ któryœ siê pojawi³
		if (lvl.timerEnemy.getElapsedTime().asSeconds() >= 1.5f){
			//ustalamy pozycjê spawnowanego czo³gu
			//Maj¹ siê pojawiaæ kolejno : po lewej, po œrodku, po prawej

			Level::NewTankPos temp = lvl.actualPos;
			switch (lvl.actualPos){
			case Level::NewTankPos::left:
				lvl.actualPos = Level::NewTankPos::mid;
				break;
			case Level::NewTankPos::mid:
				lvl.actualPos = Level::NewTankPos::right;
				break;
			case Level::NewTankPos::right:
				lvl.actualPos = Level::NewTankPos::left;
				break;
			default:
				break;
			}

			lvl.tanks.emplace_back(new Enemy{ lvl.explosions, lvl.bullets, spr, *this, lvl.tanksID, lvl.actualPos });
			if (lvl.tanks.back()->spawnCollision(lvl.tanks)){
				lvl.tanks.pop_back();
				lvl.actualPos = temp;
			}
			else{
				lvl.tanksID++;
				lvl.enemyTanks--;
				lvl.timerEnemy.restart();
			}
		}
	}
}
void Map::initiateGame(bool gameType){
	state = GameState::game;
	lvl.tanksID = { 2 };
	if (gameType) lvl.playerTanks = { 4 };
	else lvl.playerTanks = { 3 };
	lvl.timerEnemy.restart();
	lvl.actualPos = Level::NewTankPos::mid;
	setKurak();
}
void Map::endGame(){
	lvl.tanks.clear();
	lvl.bullets.clear();
}
void Map::nextLevel(){
	state = GameState::game;
}
void Map::gameOver(){
	sound.Sounds["gameOver"].play();
	while (sound.Sounds["gameOver"].getStatus() == sf::Sound::Status::Playing);
	state = GameState::exit;
}