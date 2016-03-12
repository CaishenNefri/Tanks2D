#pragma once
#include "collision.h"

class Explosion;

class Tank : public sf::Drawable, public Collision{
public:
	bool readyToShoot{ true };
	//konstruktor
	//Tank(std::list<Bullet> &, Sprite &, Map &, bool, int, Move);
	Tank(std::list<Explosion> &, std::list<Bullet> &, Sprite &, Map &, bool isPlayer = true, int ID = 0, Move move = Move::up);
	virtual ~Tank(void);

	//okreœla ruch postaci
	virtual void checkMove() = 0;

	//sprawdza czy zachodzi kolizja z wybranym blokiem
	//ustalany na podstawie pozycji + przekazywany box
	virtual bool collision(Pos, sf::FloatRect &) final;

	//Sprawdzanie kolizji z reszt¹ czo³gów
	virtual bool colWithTanks(std::list<TankPtr> &, std::list<Bullet> &, float) final;
	//virtual bool colWithTanks(std::list<TankPtr> &, float) final;

	//Sprawdzanie kolizji podczas spawn'u pojazdu
	virtual bool spawnCollision(std::list<TankPtr> &) final;

	//aktualizowanie obrazka wzglêdem zwrotu czo³gu
	virtual void updateImage() final;

	//pociski
	std::list<Bullet> & bullets;
	bool canShoot{ true };
private:
	std::list<Explosion> & explosions;
	virtual void draw(sf::RenderTarget & okno, sf::RenderStates states) const;
};