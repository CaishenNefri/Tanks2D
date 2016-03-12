#pragma once
#include <array>

#include "sprite.h"
#include "block.h"
#include "fpsClock.h"
#include "tank.h"
#include "bullet.h"
#include "explosion.h"

const int blockSIZE{ 30 };
typedef std::array < Block, blockSIZE > Blocks;
typedef std::array < Blocks, blockSIZE > BlockTab;

struct Window{
	int topBot;		//puste miejsce u góry i na dole ekranu
	int sides;		//puste pole po lewej i prawej stronie ekranu
	int blockSize;		//rozmiar bloku po zmniejszeniu
	int sideMenu;		//szerokoœæ panelu bocznego
	float scale;		//skala bloku wzglêdem jego bazowego wymiaru
	int widthInBlocks;	//szerokoœæ mapy w blokach
};
struct Level{
	enum class NewTankPos{ left, mid, right } actualPos;
	std::list<TankPtr> tanks;
	std::list<Bullet> bullets;
	std::list<Explosion> explosions;

	int levelCount;
	int actualLevel{ 0 };
	int tanksID{ 2 };
	int enemyTanks;
	int playerTanks{ 2 };
	sf::Clock timerPlayer1;
	sf::Clock timerPlayer2;
	sf::Clock timerEnemy;
	Level(int levelCount = 1) : levelCount{ levelCount }{}
};

class Map : public sf::Drawable{
public:
	Map(Sprite &, sf::RenderWindow &);
	enum class Sett { left, up, right, down, corner1, corner2, corner3, corner4, cornerBig1, cornerBig2, cornerBig3, cornerBig4, full };
	enum class GameState{ game, nextLevel, gameOver, exit };
	Window pr;
	BlockTab tab;
	Sprite & spr;
	sf::RenderWindow & okno;
	Level lvl;

	void setProperties(sf::RenderWindow & okno){
		pr.blockSize = int(okno.getSize().y / 30);
		pr.topBot = (okno.getSize().y - pr.blockSize * 30) / 2;
		pr.sideMenu = int((okno.getSize().x - pr.blockSize * 30) / pr.blockSize) * pr.blockSize;
		pr.sides = (okno.getSize().x - pr.blockSize * 30 - pr.sideMenu) / 2;
		pr.scale = float(pr.blockSize / 50.0);
		pr.widthInBlocks = 30 + pr.sideMenu / pr.blockSize;
	}
	void setSpritesProperties(){
		for (int y = 0; y < blockSIZE; y++){
			for (int x = 0; x < blockSIZE; x++){
				tab[y][x].setImg(spr);
				tab[y][x].img.setPosition(x * pr.blockSize + pr.sides, y * pr.blockSize + pr.topBot);
				tab[y][x].img.setScale(pr.scale, pr.scale);
				tab[y][x].setHardness();
				tab[y][x].setMoveMode();
			}
		}
	}
	void loadMap();
	void addEnemyTank();
	void addPlayer1Tank();
	void addPlayer2Tank();

	void events(Timer &);
	bool gameGood();
	bool checkGameStatus();
	void initiateGame(bool);
	void endGame();
	void setKurak(){
		for (int x = 0; x < 2; x++){
			for (int y = 0; y < 2; y++){
				sf::Vector2f position = tab[26 + y][14 + x].img.getPosition();
				tab[26 + y][14 + x].img = spr.kurak;
				tab[26 + y][14 + x].img.setTextureRect(sf::IntRect(x * 50,
					y * 50, 100, 100));
				tab[26 + y][14 + x].img.setPosition(position);
				tab[26 + y][14 + x].img.setScale(pr.scale, pr.scale);
				tab[26 + y][14 + x].move = Block::Move::notMoveAble;
				tab[26 + y][14 + x].type = Block::Type::kurak;
				tab[26 + y][14 + x].setHardness();
			}
		}
	}
	bool checkKurakIsLive(){
		if (tab[26][14].type == Block::Type::kurakDEAD) return 0;
		else return 1;
	}

	void nextLevel();
	void gameOver();
private:
	GameState state;
	virtual	void draw(sf::RenderTarget & okno, sf::RenderStates) const{
		for (auto y : tab){
			for (auto x : y){
				if (x.hide) continue;
				okno.draw(x.img);
			}
		}
	}
};