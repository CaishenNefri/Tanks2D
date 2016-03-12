#pragma once
#include <SFML\Graphics.hpp>
#include <list>
#include <memory>

class Tank;
class Bullet;
class Map;
class Sprite;

typedef std::unique_ptr<Tank> TankPtr;

class Collision{
public:
	Sprite & sprite;	//klasa przechowuj¹ca obrazki
	Map & map;			//klasa przechowuj¹ca mapê

	enum class Move : int { left, right, up, down, none };
	struct Pos{ int x; int y; } posMap;	//pozycja wzglêdem mapy (który blok)

	//aktualizowanie obrazka wzglêdem zwrotu objektu
	virtual void updateImage() = 0;

	//Sprawdzanie kolizji z blokami i uruchamianie kolizji z czo³gami
	virtual void checkCollision(std::list<TankPtr> &, std::list<Bullet> &);
	//virtual void checkCollision(std::list<TankPtr> &) final;

	//Metoda czysto wirtualna, która sprawdza czy zachodzi kolizja
	//z wybranym blokiem ustalanym na podstawie pozycji + przekazywany box
	virtual bool collision(Pos, sf::FloatRect &) = 0;

	//Czysto wirtualna metoda sprawdzaj¹ca kolizje z czo³gami i graczem
	virtual bool colWithTanks(std::list<TankPtr> &, std::list<Bullet> &, float) = 0;
	//virtual bool colWithTanks(std::list<Bullet>, std::list<TankPtr> &, float) = 0;

	//dane objektu
	sf::Clock timer;	//timer ograniczaj¹cy objektu
	float speed;		//szybkoœæ kolejnego przesuniêcia objektu

	sf::Vector2f pos;	//pozycja do wyœwietlania
	sf::Sprite spr;		//obrazek objektu
	Move move;			//status obrazka (w któr¹ stronê zwrócony objekt)
	Move lastMove;		//ostatni ruch (potrzebne dla pocisków)
	const int objID;	//numer ID objektu

	bool exist{ true };	//okreœla czy obiekt istnieje

	Collision(Sprite &, Map &, bool, int, Move);

	const bool player;

	virtual ~Collision(void){}
};