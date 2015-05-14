#ifndef TILE_H
#define TILE_H

#include "Main.h"

enum TileCollision
{
	passable = 0,

	unpassable = 1,

	checkpoint = 2,

	item = 3,

	goalLine = 4,
};

class Tile
{
public:
	Tile();
	~Tile();

	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<sf::Vector2i> tempMap;
	sf::Texture tileTexture;
	sf::Sprite tiles;

	std::vector<std::vector<int>> colMap;
	std::vector<int> tempMap2;

	sf::Vector2i tilePos;

	void loadTileMap();
	void loadColMap();
};

#endif