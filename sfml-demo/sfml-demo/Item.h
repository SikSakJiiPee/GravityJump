#ifndef ITEM_H
#define ITEM_H

#include "Main.h"

enum Items
{
	speedBoost = 0,

	swapPlaces = 1,

	teleport = 2,

};

class Item
{
public:
	Item();

	bool itemUsed = false;

	void randomItem();

	~Item();
};

#endif