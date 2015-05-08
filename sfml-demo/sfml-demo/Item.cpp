#include "Item.h"




Item::Item()
{
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
		g = rand() % 2;
		std::cout << "Randoming";
		switch (g)
		{
		case 1:
		{
			std::cout << "Speed boost";
			hasItem = true;
			//std::cout << "Item test 0";
			//speedboost
			activeItem = speedBoost;
			
			
			break;
		}
		case 2:
		{

			activeItem = setBack;
			//std::cout << "Item test 1";
			//Set opponent back to latest checkpoint
			break;
		}
		
		}	
	}
}