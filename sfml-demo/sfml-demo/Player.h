#ifndef PLAYER_H
#define PLAYER_H


#include "Tile.h"

class Player
{
public:
	Player();
	Player(int playerID, sf::Vector2f position, sf::Texture &playerTexture);
	~Player();

	int playerIndex;

	sf::Sprite playerSprite;
	sf::Image playerImg;
	std::vector<sf::Vector2i> tilesP;

	void Update(sf::Texture &playerTexture, Tile &tile);

	bool collisionLeft(Player p);
	bool collisionTop(Player p);
	bool collisionBottom(Player p);
	bool collisionRight(Player p);

	sf::Vector2f playerPos;

	bool collidingWall = false;

	bool movingLeft = false;
	bool movingRight = false;
	bool movingUp = false;
	bool movingDown = false;

	bool collidingRight = false;
	bool collidingLeft = false;
	bool collidingDown = false;
	bool collidingUp = false;

	float bottom, left, right, top;

protected:
	
	
};

#endif