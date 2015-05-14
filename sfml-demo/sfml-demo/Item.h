#ifndef ITEM_H
#define ITEM_H


#include "Main.h"

enum Items
{
	speedBoost = 1,

	setBack = 2,

	

};

class Item
{
public:
	Item();

	bool itemUsed = false;
	bool hasItem = false;
	int activeItem = 0;
	void randomItem();
	sf::Sound speedBoostSFX;
	sf::Sound setBackSFX;
	sf::SoundBuffer setBackBuf;
	sf::SoundBuffer speedBoostBuf;
	~Item();
};

#endif