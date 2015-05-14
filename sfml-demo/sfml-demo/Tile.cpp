#include "Tile.h"

Tile::Tile()
{

	//loadColMap();
	//loadTileMap();
}


Tile::~Tile()
{
}

void Tile::loadTileMap()
{
	std::ifstream openfile("Map1.txt");
	tempMap.clear();
	map.clear();



	if (openfile.is_open())
	{
		std::cout << "TileMap open" << std::endl;
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
			if (tempMap.size() > 0)
			{
				map.push_back(tempMap);
				tempMap.clear();
			}
		}

	}
}

void Tile::loadColMap()
{
	std::ifstream openfile2("Map1col.txt");
	std::cout << "Collision Map open" << std::endl;
	tempMap2.clear();
	colMap.clear();

	if (openfile2.is_open())
	{

		while (!openfile2.eof())
		{
			std::string str, value;
			std::getline(openfile2, str);
			std::stringstream stream(str);

			while (std::getline(stream, value, ' ')) // K‰yd‰‰n l‰pi Map1col.txt rivi kerrallaan
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
}