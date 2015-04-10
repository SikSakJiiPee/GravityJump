#include "Player.h"
#include "Main.h"

std::vector<std::vector<bool>> mask;



Player::Player(sf::Vector2f position, sf::Texture &playerTexture)
{
	playerImg = playerTexture.copyToImage();
	
	for (int i = 0; i < playerImg.getSize().x; i++)
	{
		std::vector<bool> tempMask;
		for (int j = 0; j < playerImg.getSize().y; j++)
		{
			if (playerImg.getPixel(i, j).a > 0)
				tempMask.push_back(true);
			else
				tempMask.push_back(false);
		}
		mask.push_back(tempMask);
	}
	playerSprite.setPosition(position);
	playerSprite.setTexture(playerTexture);
}

Player::~Player()
{
}

void Player::Update(sf::Texture &playerTexture, Tile &tile)
{
	playerImg = playerTexture.copyToImage();

	bottom = playerSprite.getPosition().y + playerImg.getSize().y;
	left = playerSprite.getPosition().x;
	right = playerSprite.getPosition().x + playerImg.getSize().x;
	top = playerSprite.getPosition().y;

	// Tarkastetaan collisiota vain kulmista
	sf::Vector2i topLeft(sf::Vector2i((int)left / 32, (int)top / 32));
	sf::Vector2i topRight(sf::Vector2i((int)right / 32, (int)top / 32));
	sf::Vector2i bottomLeft(sf::Vector2i((int)left / 32, (int)bottom / 32));
	sf::Vector2i bottomRight(sf::Vector2i((int)right / 32, (int)bottom / 32));

	playerPos = playerSprite.getPosition();

	tilesP.clear();

	tilesP.push_back(topLeft);

	if (std::find(tilesP.begin(), tilesP.end(), topRight) == tilesP.end())
	{
		tilesP.push_back(topRight);
	}

	if (std::find(tilesP.begin(), tilesP.end(), bottomLeft) == tilesP.end())
	{
		tilesP.push_back(bottomLeft);
	}

	if (std::find(tilesP.begin(), tilesP.end(), bottomRight) == tilesP.end())
	{
		tilesP.push_back(bottomRight);
	}

	//----
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && collidingRight == false) // Oikealle liikkuminen
	{
		playerSprite.move(4, 0);
		movingRight = true;
		collidingLeft = false;
	}
	else
		movingRight = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && collidingLeft == false) // Vasemmalle liikkuminen
	{
		playerSprite.move(-4, 0);
		movingLeft = true;
		collidingRight = false;
	}
	else
		movingLeft = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && collidingUp == false) // Ylöspäin liikkuminen
	{
		playerSprite.move(0, -4);
		movingUp = true;
		collidingDown = false;
	}
	else
		movingUp = false;

	if (collidingUp == true)
	{
		std::cout << "Colliding up";
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && collidingDown == false) // Alaspäin liikkuminen
	{
		playerSprite.move(0, 4);
		movingDown = true;
		collidingUp = false;

	}
	else
		movingDown = false;
	//LIIKKUMINEN LOPPU

	if (collidingRight == true)
	{
		//playerSprite.move(-4, 0);

		playerSprite.setPosition(playerSprite.getPosition().x - 4, playerSprite.getPosition().y);
		collidingLeft = false;
		//collidingWall = false;
	}


	if (collidingLeft == true)
	{
		//playerSprite.move(4, 0);
		playerSprite.setPosition(playerSprite.getPosition().x + 4, playerSprite.getPosition().y);
		collidingRight = false;
		//collidingWall = false;
	}


	if (collidingUp == true)
	{
		//playerSprite.move(0, 4);
		playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y + 4);
		collidingDown = false;
	}


	if (collidingDown == true)
	{
		//playerSprite.move(0, -4);
		playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y - 4);
		collidingUp = false;
	}



	for (int i = 0; i < tilesP.size(); i++)
	{
		if (tile.colMap[tilesP[i].y][tilesP[i].x] == unpassable)
		{
			if (movingUp == true)
			{
				collidingUp = true;


				tile.tilePos = tile.tiles.getPosition();



				//Etsitään mihin tileihin osutaan
				//Käydään läpi tilet
				//Tehdään tarvittava korjaus

			}
			else if (movingDown == true)
			{
				collidingDown = true;
			}
			else if (movingLeft == true)
			{
				collidingLeft = true;
			}
			else if (movingRight == true)
			{
				collidingRight = true;
			}
			//std::cout << "ITS A WALL ";
			break;

		}
		else if (tile.colMap[tilesP[i].y][tilesP[i].x] == trap)
		{
			std::cout << "ITS A TARP!";
			break;
		}
		else
		{
			collidingUp = false;
			collidingDown = false;
			collidingLeft = false;
			collidingRight = false;
		}
	}
}



bool Player::collisionLeft(Player p)
{
	if (right < p.left || left > p.right || top > p.bottom || bottom < p.top)
	{
		return false;
	}
	else // if (left < p.right && right > p.left + 20)
	{
		return true;
	}
}
bool Player::collisionRight(Player p)
{
	if (right < p.left  || left > p.right || top > p.bottom || bottom < p.top)
	{
		return false;
	}
	else if (right > p.left && left < p.right - 16)
	{
		return true;
	}
}
bool Player::collisionTop(Player p)
{
	if (right < p.left || left > p.right || top > p.bottom || bottom < p.top)
	{
		return false;
	}
	else if (top < p.bottom && bottom > p.top + 16)
	{
		return true;
	}
}
bool Player::collisionBottom(Player p)
{
	if (right < p.left || left > p.right || top > p.bottom || bottom < p.top)
	{
		return false;
	}
	else if (bottom > p.top && top < p.bottom - 16)
	{
		return true;
	}
}
