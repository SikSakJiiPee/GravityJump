#include "Main.h"
#include "Player.h"



int main()
{

	sf::RenderWindow window(sf::VideoMode(640, 480, 32), "GravityJump 0.02");
	window.setFramerateLimit(60);


	sf::Texture playerTex;
	playerTex.loadFromFile("Texture/player1.png");

	Player p1(Player(sf::Vector2f(6, -10), playerTex));

	sf::FloatRect boundingBox = p1.playerSprite.getGlobalBounds();

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
			std::cout << "File open";
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

				window.clear(sf::Color(0, 240,255));

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
				window.draw(p1.playerSprite);
			
				window.display();

#pragma region Liikkuminen
						//LIIKKUMINEN
				
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						{
							p1.playerSprite.move(4.5, 0);
						
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						{
							p1.playerSprite.move(-4.5, 0);
					
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						{
							p1.playerSprite.move(0, -4.5);
						
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							p1.playerSprite.move(0, 4.5);
						}	
						//LIIKKUMINEN LOPPU
#pragma endregion Liikkuminen

						p1.Update(playerTex);

						//Collision check
						for (int i = 0; i < p1.tilesP.size(); i++)
						{
							if (colMap[p1.tilesP[i].y][p1.tilesP[i].x] == 1)
							{
								std::cout << "collision";
								break;
							}
						}
						

			}

}

