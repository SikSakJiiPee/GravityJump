#include "Player.h"
#include "Main.h"
#include "Item.h"

std::vector<std::vector<bool>> mask;



Player::Player(int playerID, sf::Vector2f position, sf::Texture &playerTexture)
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
	playerIndex = playerID;
}

Player::~Player()
{
}

void Player::Update(sf::Texture &playerTexture, Tile &tile)
{
	Item items;

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
	//LIIKKUMINEN
	//Näppäimistö
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
		//std::cout << "Colliding up";
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && collidingDown == false) // Alaspäin liikkuminen
	{
		playerSprite.move(0, 4);
		movingDown = true;
		collidingUp = false;

	}
	else
		movingDown = false;

	//Ohjain
	if (sf::Joystick::isConnected(0))
	{
		unsigned int buttonCount = sf::Joystick::getButtonCount(0);
		//std::cout << buttonCount << std::endl;
		// Xinput: 10 (Xbox) , Dinput: 12 (Wii U)

		//Näppäinten tunnistus
		if (sf::Joystick::isButtonPressed(0, 0))
		{
			std::cout << "P1 painike Y painettu" << std::endl;
			//player1Spr.setRotation(90);
			std::cout << "P1 Rotate left" << std::endl;
		}
		if (sf::Joystick::isButtonPressed(0, 1))
		{
			std::cout << "P1 painike B painettu" << std::endl;
			//player1Spr.setRotation(0);
			std::cout << "P1 Rotate down" << std::endl;
		}
		if (sf::Joystick::isButtonPressed(0, 2))
		{
			std::cout << "P1 painike A painettu" << std::endl;
			//player1Spr.setRotation(270);
			std::cout << "P1 Rotate right" << std::endl;
		}
		if (sf::Joystick::isButtonPressed(0, 3))
		{
			std::cout << "P1 painike X painettu" << std::endl;
			//player1Spr.setRotation(180);
			std::cout << "P1 Rotate up" << std::endl;
		}
		if (sf::Joystick::isButtonPressed(0, 4))
		{
			std::cout << "P1 painike L painettu" << std::endl;
		}
		if (sf::Joystick::isButtonPressed(0, 5))
		{
			std::cout << "P1 painike R painettu" << std::endl;
		}
		if (sf::Joystick::isButtonPressed(0, 6))
		{
			std::cout << "P1 painike ZL painettu" << std::endl;
		}
		if (sf::Joystick::isButtonPressed(0, 7))
		{
			std::cout << "P1 painike LR painettu" << std::endl;
		}
		if (sf::Joystick::isButtonPressed(0, 8))
		{
			std::cout << "P1 painike SELECT painettu" << std::endl;
		}
		if (sf::Joystick::isButtonPressed(0, 9))
		{
			std::cout << "P1 painike START painettu" << std::endl;
		}
		if (sf::Joystick::isButtonPressed(0, 10))
		{
			std::cout << "P1 painike L STCK painettu" << std::endl;
		}
		if (sf::Joystick::isButtonPressed(0, 11))
		{
			std::cout << "P1 painike R STICK painettu" << std::endl;
		}
	}
	if (sf::Joystick::isConnected(0))
	{
		float axisX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		if (axisX > 50 && collidingRight == false) // Oikealle liikkuminen
		{
			playerSprite.move(4, 0);
			movingRight = true;
			collidingLeft = false;
		}
		else
			movingRight = false;

		if (axisX < -50 && collidingLeft == false) // Vasemmalle liikkuminen
		{
			playerSprite.move(-4, 0);
			movingLeft = true;
			collidingRight = false;
		}
		else
			movingLeft = false;

		float axisY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		if (axisY < -50 && collidingUp == false) // Ylöspäin liikkuminen
		{
			playerSprite.move(0, -4);
			movingUp = true;
			collidingDown = false;

		}
		else
			movingUp = false;

		if (collidingUp == true)
		{
			//std::cout << "Colliding up";
		}

		if (axisY > 50 && collidingDown == false) // Alaspäin liikkuminen
		{
			playerSprite.move(0, 4);
			movingDown = true;
			collidingUp = false;

		}
		else
			movingDown = false;

	}

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
