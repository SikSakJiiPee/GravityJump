#ifndef PLAYER_H
#define PLAYER_H


#include "Tile.h"
#include "Main.h"
#include "Item.h"
#include "Background.h"
#include "Credits.h"

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
	void setBackFunct(Player &p1, Player &p2);
	bool activatedSetBack = false;

	bool gameEnd = false;


	sf::Clock clock;
	void setCheckpoint(Tile &tile);
	void loadCheckpoint();
	void getPlayerdistance(Player &p1, Player &p2);

	sf::Vector2f playerDistance;
	bool onRange = false;

	sf::Vector2f playerPos;
	sf::Vector2f currentCheckpoint;
	sf::Vector2f playerOrigin;

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