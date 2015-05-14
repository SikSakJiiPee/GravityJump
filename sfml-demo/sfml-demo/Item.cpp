#include "Item.h"


Item::Item()
{

	
	setBackBuf.loadFromFile("SFX/set_back.wav");
		
	
	setBackSFX.setBuffer(setBackBuf);

	
	speedBoostBuf.loadFromFile("SFX/speed_boost.wav");
	
	
	speedBoostSFX.setBuffer(speedBoostBuf);


}


Item::~Item()
{
}


void Item::randomItem()
{	



	int g;

	if (hasItem == true)
	{
		if (itemUsed == true)
		{
			hasItem = false;
		}
		else
		std::cout << "Already have item";
	}
	else if (hasItem == false) // Jos ei ole itemiä, randomoidaan itemi
	{
		g = rand() % 2 + 1;
		std::cout << "Randoming";
		switch (g)
		{
		case 1:
		{

			speedBoostSFX.play();
			hasItem = true;
			//std::cout << "Item test 0";
			//speedboost
			activeItem = speedBoost;
			
			
			break;
		}
		case 2:
		{
			setBackSFX.play();
			hasItem = true;
			activeItem = setBack;
			//Set opponent back to latest checkpoint
			break;
		}
		
		}	
	}
}

