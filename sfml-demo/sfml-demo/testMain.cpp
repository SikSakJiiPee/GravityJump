#include "Main.h"
#include "Player.h"



int main()
{
	sf::Vector2i screenDimensions(640, 480);

	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y, 32), "GravityJump 0.02");
	window.setFramerateLimit(60);


	sf::Texture playerTex;
	playerTex.loadFromFile("Texture/testi.png");

	sf::Texture backgroundTex;
	sf::Sprite backgroundImg;
	backgroundTex.loadFromFile("Texture/backround1.jpg");

	backgroundImg.setTexture(backgroundTex);
	backgroundImg.setScale(1.0f, (float)screenDimensions.y / backgroundTex.getSize().y);

	Player p1(Player(sf::Vector2f(70, 40), playerTex));

	bool collidingWall = false;

	bool movingLeft = false;
	bool movingRight = false;
	bool movingUp = false;
	bool movingDown = false;

	bool collidingRight = false;
	bool collidingLeft = false;
	bool collidingDown = false;
	bool collidingUp = false;


	sf::View view1, view2;

	view1.setViewport(sf::FloatRect(0, 0, 0.5f, 1.0f));
	view1.setSize(screenDimensions.x / 2, screenDimensions.y);

	view2.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1.0f));
	view2.setSize(screenDimensions.x / 2, screenDimensions.y);

	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
	sf::Vector2f position2(position);

#pragma region TileMap

	//Ladataan kenttä ------------------------
	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<sf::Vector2i> tempMap;
	sf::Texture tileTexture;
	sf::Sprite tiles;

	
		std::ifstream openfile("Map1.txt");
		tempMap.clear();
		map.clear();



		if (openfile.is_open())
		{
			std::cout << "TileMap open";
			std::string tileLocation;
			openfile >> tileLocation;
			tileTexture.loadFromFile(tileLocation);
			tiles.setTexture(tileTexture);

			while (!openfile.eof())
			{
				std::string str, value;
				std::getline(openfile, str);
				std::stringstream stream(str);

				while (std::getline(stream, value, ' ')) // Käydään läpi Map1.txt rivi kerrallaan
				{
					if (value.length() > 0)
					{
						std::string xx = value.substr(0, value.find(',')); // Etsitään arvo ennen pilkkua
						std::string yy = value.substr(value.find(',') + 1); // Etsitään arvo pilkun jälkeen

						int x, y, i, j;

						for (i = 0; i < xx.length(); i++)
						{
							if (!isdigit(xx[i]))
								break;
						}
						for (j = 0; j < yy.length(); j++)
						{
							if (!isdigit(yy[j]))
								break;
						}

						x = (i == xx.length()) ? atoi(xx.c_str()) : -1; // IF i == length of xx. atoi converts string to int 
						y = (j == yy.length()) ? atoi(yy.c_str()) : -1;	// IF j == length of yy. atoi converts string to int 

						tempMap.push_back(sf::Vector2i(x, y));
					}
				}
				if (tempMap.size() > 0)
				{
					map.push_back(tempMap);
					tempMap.clear();
				}
			}

		}
	// KENTÄN LATAUS LOPPUU
#pragma endregion TileMap

#pragma region CollisionMap
	// LADATAAN COLLISION MAP 
		std::vector<std::vector<int>> colMap;
		std::vector<int> tempMap2;
		
		std::ifstream openfile2("Map1col.txt");
		tempMap2.clear();
		colMap.clear();

		if (openfile2.is_open())
		{

			while (!openfile2.eof())
			{
				std::string str, value;
				std::getline(openfile2, str);
				std::stringstream stream(str);

				while (std::getline(stream, value, ' ')) // Käydään läpi Map1col.txt rivi kerrallaan
				{
					if (value.length() > 0)
					{
						int a = atoi(value.c_str()); // Muutetaan string - intiksi
						tempMap2.push_back(a);
					}
				}
				colMap.push_back(tempMap2);
				tempMap2.clear();
			}

		}
#pragma endregion CollisionMap

			while (window.isOpen())
			{
				
				sf::Event event;
				while (window.pollEvent(event))
				{
					switch (event.type)
					{
					case sf::Event::Closed:
						window.close();
						break;
					}
					
				}

				window.setView(view1);
				
				window.draw(backgroundImg);

				for (int c = 0; c < map.size(); c++)
				{
					for (int g = 0; g < map[c].size(); g++)
					{
						if (map[c][g].x != -1 && map[c][g].y != -1)
						{
							tiles.setPosition(g * 32, c * 32);
							tiles.setTextureRect(sf::IntRect(map[c][g].x * 32, map[c][g].y * 32, 32, 32));
							window.draw(tiles);
						}
					}
				}
				if (p1.playerSprite.getPosition().x + 10 >= view1.getSize().x / 2)
					position.x = p1.playerSprite.getPosition().x + 10;
				else
					position.x = view1.getSize().x / 2;

				if (p1.playerSprite.getPosition().y + 10 >= view1.getSize().y / 2)
					position.y = p1.playerSprite.getPosition().y + 10;
				else
					position.y = view1.getSize().y / 2;

				view1.setCenter(position);
				view2.setCenter(position2);

				
				window.draw(p1.playerSprite);
				
				window.setView(view2);
				window.draw(backgroundImg);
				window.draw(p1.playerSprite);
				for (int c = 0; c < map.size(); c++)
				{
					for (int g = 0; g < map[c].size(); g++)
					{
						if (map[c][g].x != -1 && map[c][g].y != -1)
						{
							tiles.setPosition(g * 32, c * 32);
							tiles.setTextureRect(sf::IntRect(map[c][g].x * 32, map[c][g].y * 32, 32, 32));
							window.draw(tiles);
						}
					}
				}

				window.display();
				window.clear();

#pragma region Liikkuminen
						//LIIKKUMINEN
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && collidingRight == false) // Oikealle liikkuminen
				{
					
						p1.playerSprite.move(4, 0);
						movingRight = true;

					if (collidingWall == false)
					{
							collidingRight = false;
							collidingUp = false;
							collidingDown = false;
							collidingLeft = false;
					}

					collidingLeft = false;
				}
				else
				movingRight = false;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&& collidingLeft == false) // Vasemmalle liikkuminen
				{
							p1.playerSprite.move(-4, 0);
							movingLeft = true;

							if (collidingWall == false)
							{
								collidingRight = false;
								collidingUp = false;
								collidingDown = false;
								collidingLeft = false;
							}

							collidingRight = false;
				}
				else
				movingLeft = false;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& collidingUp == false) // Ylöspäin liikkuminen
				{
					p1.playerSprite.move(0, -4);
					movingUp = true;
					if (collidingWall == false)
					{
						collidingRight = false;
						collidingUp = false;
						collidingDown = false;
						collidingLeft = false;
					}

					collidingDown = false;
				}
				else
				movingUp = false;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& collidingDown == false) // Alaspäin liikkuminen
				{
					p1.playerSprite.move(0,4);
					movingDown = true;

					if (collidingWall == false)
					{
						collidingRight = false;
						collidingUp = false;
						collidingDown = false;
						collidingLeft = false;
					}
					collidingUp = false;
				}	
				else
				movingDown = false;
						//LIIKKUMINEN LOPPU

				if (movingRight == true && collidingWall == true && collidingLeft == false)
				{
					p1.playerSprite.move(-4, 0);
					p1.playerSprite.setPosition(p1.playerSprite.getPosition().x - 5, p1.playerSprite.getPosition().y);
					collidingRight = true;
					collidingLeft = false;
					//collidingWall = false;
				}
				

				if (movingLeft == true && collidingWall == true && collidingRight == false)
				{
					p1.playerSprite.move(4, 0);
					p1.playerSprite.setPosition(p1.playerSprite.getPosition().x + 5, p1.playerSprite.getPosition().y);
					collidingLeft = true;
					collidingRight = false;
					//collidingWall = false;
				}
			

				if (movingUp == true && collidingWall == true && collidingDown == false)
				{
					p1.playerSprite.move(0, 4);
					p1.playerSprite.setPosition(p1.playerSprite.getPosition().x, p1.playerSprite.getPosition().y + 5);
					collidingUp = true;
					collidingDown = false;
				}
			

				if (movingDown == true && collidingWall == true && collidingUp == false)
				{
					p1.playerSprite.move(0, -4);
					p1.playerSprite.setPosition(p1.playerSprite.getPosition().x, p1.playerSprite.getPosition().y - 5);
					collidingDown = true;
					collidingUp = false;
				}
				
				if (collidingDown == true)
				{
					collidingUp = false;
				}

				if (collidingLeft == true)
				{
					collidingRight = false;
				}

			
				
#pragma endregion Liikkuminen
				
						p1.Update(playerTex);
					
						//Collision check
						for (int i = 0; i < p1.tilesP.size(); i++)
						{
							if (colMap[p1.tilesP[i].y][p1.tilesP[i].x] == 1)
							{
								collidingWall = true;
								//std::cout << "ITS A WALL ";
								break;
							}
							else if (colMap[p1.tilesP[i].y][p1.tilesP[i].x] == 2)
							{
								std::cout << "ITS A TARP!";
								break;
							}
							else
							{
								collidingWall = false;
							}
						}
						

			}

}

