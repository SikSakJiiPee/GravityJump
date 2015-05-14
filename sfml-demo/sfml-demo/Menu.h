#ifndef MENU_H
#define MENU_H

#include "Main.h"


#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu(sf::RenderWindow *window);
	~Menu();

	void draw(sf::RenderWindow *window);
	void Moveup();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }
	
	void getWindowWidth();
	void getWindowHeight();

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

#endif