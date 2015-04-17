#include "Item.h"

bool hasItem = false;

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
		std::cout << "Already have ";
	}
	else if (hasItem == false) // Jos ei ole itemiä, randomoidaan itemi
	{
		g = rand() % 3;
		std::cout << "Randoming";
		switch (g)
		{
		case 0:
		{
			hasItem = true;
			//std::cout << "Item test 0";
			//speedboost
			break;
		}
		case 1:
		{
			hasItem = true;
			//std::cout << "Item test 1";
			break;
		}
		case 2:
		{
			hasItem = true;
			//std::cout << "Item test 2";
			break;
		}
		}
	
	}
	

	

}