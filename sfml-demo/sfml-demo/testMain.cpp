#include "Main.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480, 32), "Tilemap demo");
	window.setFramerateLimit(60);


	std::ifstream openfile("Map1.txt");
	sf::Texture tileTexture;
	sf::Sprite tiles;

	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<sf::Vector2i> tempMap;

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

			while (std::getline(stream, value, ' ')) // K‰yd‰‰n l‰pi Map1.txt rivi kerrallaan
			{
				if (value.length() > 0)
				{
					std::string xx = value.substr(0, value.find(',')); // Etsit‰‰n arvo ennen pilkkua
					std::string yy = value.substr(value.find(',') + 1); // Etsit‰‰n arvo pilkun j‰lkeen

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
			map.push_back(tempMap);
			tempMap.clear();
		}
	}
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
				window.display();
			}

}

