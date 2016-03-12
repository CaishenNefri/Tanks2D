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
	Sprite & sprite;	//klasa przechowuj�ca obrazki
	Map & map;			//klasa przechowuj�ca map�

	enum class Move : int { left, right, up, down, none };
	struct Pos{ int x; int y; } posMap;	//pozycja wzgl�dem mapy (kt�ry blok)

	//aktualizowanie obrazka wzgl�dem zwrotu objektu
	virtual void updateImage() = 0;

	//Sprawdzanie kolizji z blokami i uruchamianie kolizji z czo�gami
	virtual void checkCollision(std::list<TankPtr> &, std::list<Bullet> &);
	//virtual void checkCollision(std::list<TankPtr> &) final;

	//Metoda czysto wirtualna, kt�ra sprawdza czy zachodzi kolizja
	//z wybranym blokiem ustalanym na podstawie pozycji + przekazywany box
	virtual bool collision(Pos, sf::FloatRect &) = 0;

	//Czysto wirtualna metoda sprawdzaj�ca kolizje z czo�gami i graczem
	virtual bool colWithTanks(std::list<TankPtr> &, std::list<Bullet> &, float) = 0;
	//virtual bool colWithTanks(std::list<Bullet>, std::list<TankPtr> &, float) = 0;

	//dane objektu
	sf::Clock timer;	//timer ograniczaj�cy objektu
	float speed;		//szybko�� kolejnego przesuni�cia objektu

	sf::Vector2f pos;	//pozycja do wy�wietlania
	sf::Sprite spr;		//obrazek objektu
	Move move;			//status obrazka (w kt�r� stron� zwr�cony objekt)
	Move lastMove;		//ostatni ruch (potrzebne dla pocisk�w)
	const int objID;	//numer ID objektu

	bool exist{ true };	//okre�la czy obiekt istnieje

	Collision(Sprite &, Map &, bool, int, Move);

	const bool player;

	virtual ~Collision(void){}
};