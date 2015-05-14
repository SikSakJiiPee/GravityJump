#ifndef PLAYER_H
#define PLAYER_H


#include "Tile.h"
#include "Main.h"
#include "Item.h"
#include "Background.h"

class Player
{
public:
	Player();
	Player(sf::Vector2f position, sf::Texture &playerTexture,int playerID);
	~Player();

	sf::Sprite playerSprite;
	sf::Image playerImg;
	std::vector<sf::Vector2i> tilesP;
	int ID = 0;

	int playerSpeed = 4;
	int origPlayerSpeed = 4;

	void Update(sf::Texture &playerTexture, Tile &tile);

	void useItem();
	sf::Clock clock;
	void setCheckpoint(Tile &tile);
	void loadCheckpoint();

	sf::Vector2f playerPos;
	sf::Vector2f currentCheckpoint;

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