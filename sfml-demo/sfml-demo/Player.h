#ifndef PLAYER_H
#define PLAYER_H

#include "Main.h"

class Player
{
public:
	Player();
	~Player();

	Player(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	sf::RectangleShape rect;
	void Update();
	bool collisionLeft(Player p);
	bool collisionTop(Player p);
	bool collisionBottom(Player p);
	bool collisionRight(Player p);

protected:
	
	float bottom, left, right, top;
};

#endif