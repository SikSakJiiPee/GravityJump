#ifndef TILE_H
#define TILE_H

enum TileCollision
{
	passable = 0,

	unpassable = 1,

	platform = 2,

	trap = 3,

	item = 4,

};

class Tile
{
public:



	Tile();
	~Tile();
};

#endif