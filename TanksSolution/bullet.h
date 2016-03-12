#pragma once
#include <SFML\Graphics.hpp>

#include "collision.h"

class Map;

class Bullet : public sf::Drawable, public Collision{
public:
	Bullet(Sprite &, Map &, sf::Vector2f, int, Move, bool);

	void setStartPos(sf::Vector2f);
	virtual bool collision(Pos, sf::FloatRect &) final;
	virtual bool colWithTanks(std::list<TankPtr> &, std::list<Bullet> &, float) final;
	virtual void checkCollision(std::list<TankPtr> &, std::list<Bullet> &) override;

	//aktualizowanie obrazka wzglêdem zwrotu objektu
	virtual void updateImage() final;

	bool colWithBullets(std::list<Bullet> &, sf::FloatRect &);
private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
};