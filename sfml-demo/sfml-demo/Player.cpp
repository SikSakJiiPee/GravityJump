#include "Player.h"

std::vector<std::vector<bool>> mask;
Item items;

Player::Player(sf::Vector2f position, sf::Texture &playerTexture, int playerID)
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

	
	

	
	ID = playerID;
	
}

Player::~Player()
{
}

void Player::Update(sf::Texture &playerTexture, Tile &tile, sf::Clock clock)
{
	
	sf::Time cooldown = clock.getElapsedTime();

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



	switch (ID)
	{
	case 1:
		//---- PLAYER 1 Controlls
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && collidingRight == false) // Oikealle liikkuminen
		{
			playerSprite.move(playerSpeed, 0);
			movingRight = true;
			collidingLeft = false;
		}
		else
			movingRight = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && collidingLeft == false) // Vasemmalle liikkuminen
		{
			playerSprite.move(-playerSpeed, 0);
			movingLeft = true;
			collidingRight = false;
		}
		else
			movingLeft = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && collidingUp == false) // Ylöspäin liikkuminen
		{
			playerSprite.move(0, -playerSpeed);
			movingUp = true;
			collidingDown = false;

		}
		else
			movingUp = false;

		if (collidingUp == true)
		{
			//std::cout << "Colliding up";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && collidingDown == false) // Alaspäin liikkuminen
		{
			playerSprite.move(0, playerSpeed);
			movingDown = true;
			collidingUp = false;

		}
		else
			movingDown = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			
			std::cout << "test";
			//ITAM HAPPENING
    			if (items.hasItem == true)
			{
				//if (items.activeItem == speedBoost)
				//{
				//	playerSpeed = 6;
				//	std::cout << "BOOOOOST";
				//	items.itemUsed = true;

				//	

				//	while (cooldown.asSeconds() <= 3.0f)
				//	{
				//		std::cout << "Cooldown over";
				//		
				//	}
				//	//std::cout << "Boost over";
				//}
			}

			
		}
		
		break;
		//--- P1 CONTRL END
	case 2:

		//Player2 Controlls ----
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && collidingRight == false) // Oikealle liikkuminen
		{
			playerSprite.move(playerSpeed, 0);
			movingRight = true;
			collidingLeft = false;
		}
		else
			movingRight = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && collidingLeft == false) // Vasemmalle liikkuminen
		{
			playerSprite.move(-playerSpeed, 0);
			movingLeft = true;
			collidingRight = false;
		}
		else
			movingLeft = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && collidingUp == false) // Ylöspäin liikkuminen
		{
			playerSprite.move(0, -playerSpeed);
			movingUp = true;
			collidingDown = false;

		}
		else
			movingUp = false;

		if (collidingUp == true)
		{
			//std::cout << "Colliding up";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && collidingDown == false) // Alaspäin liikkuminen
		{
			playerSprite.move(0, playerSpeed);
			movingDown = true;
			collidingUp = false;

		}
		else
			movingDown = false;
		break;
	}
	//------- P2 CONTRL END

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



	for (int i = 0; i < tilesP.size(); i++) //Käydään pelaajan kulmat läpi
	{
		if (tile.colMap[tilesP[i].y][tilesP[i].x] == unpassable) //Jos pelaajan kulma osuu seinään
		{
			if (movingUp == true)
			{
				collidingUp = true;

				for (int j = 0; j < tile.colMap.size(); j++) //Etsitään collision mapista osutun tilen x-paikka (J) - Ei varmaan oikea tapa tällä hetkellä
				{
					for (int i = 0; i < tile.colMap[j].size(); i++) //Etsitään collision mapista osutun tilen y-paikka (i) - Ei varmaan oikea tapa tällä hetkellä
					{
						// JOS - joku ehto juttu juttelson
						if (tile.colMap[tilesP[i].y][tilesP[i].x] != -1 && tile.colMap[tilesP[i].y][tilesP[i].x] != -1)
						{
							//kerrotaan collision mapin x-y paikat 32:lla jotta saadaan pikseleinä koordinaatit. Ja tehdään korjaus jotta saadaan tilen keskipiste +16 -16 (x / y) riippuen mistä suunnasta osutaan. 
							std::cout << tilesP[i].x;

							std::cout << tilesP[i].y;//Näillä laitetaan toimimaan !

							//std::cout << i;
							//Haetaan pelaajan keskipiste - katsotaan etäisyys tilen keskipisteeseen jos etäisyys vähemmän kuin 32pikseliä - siirretään pelaajaa menosuunnan vastaiseen suuntaan (32 - etäisyys) verran.
							j * 32 + 16;
							i * 32 + 16;

							tile.tilePos.x = j;
							tile.tilePos.y = i;

							break;
						}
					}
				}

				
				//std::cout << tile.tilePos.x << std::endl;
				//std::cout << tile.tilePos.y;



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
		else if (tile.colMap[tilesP[i].y][tilesP[i].x] == item)
		{
			items.randomItem();

			clock.restart();

			tile.colMap[tilesP[i].y][tilesP[i].x] = passable;
			std::cout << "Itam";

			

			 // poistetaan itemi paikalta.
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
