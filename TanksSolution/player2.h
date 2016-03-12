#include "player.h"

class Player2 : public Player{
public:
	Player2(std::list<Explosion> & explosions, std::list<Bullet> & bullets, Sprite & sprite, Map & map, bool isPlayer = true, int ID = 1, Move move = Move::up)
		: Player{ explosions, bullets, sprite, map, isPlayer, ID, move }
	{
		speed = { 0.033f };

		spr = sprite.tankGreen;

		pos.x = float(map.pr.sides + map.pr.blockSize * 17);
		pos.y = float(map.pr.topBot + map.pr.blockSize * 26);

		spr.setPosition(pos);
		spr.setScale(map.pr.scale, map.pr.scale);

		updateImage();
		this->move = Move::none;
	}
	virtual ~Player2(void){}

	void checkMove() override{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
			lastMove = move = Move::up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
			lastMove = move = Move::down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
			lastMove = move = Move::left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
			lastMove = move = Move::right;
		}
		else{
			if (move != Move::none) lastMove = move;
			move = Move::none;
		}
	}
};