#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Main.h"

class Background
{
public:
	Background();

	void Update(sf::RenderWindow &window);
	void Render(sf::RenderWindow &window);

	~Background();

private:
	sf::Texture backgroundTex;
	sf::Sprite backgroundImg;

	

	sf::RectangleShape bgShape;
	sf::Vector2f bgSize;

	float bgSpeed;
	float bgY;
	float windowBgDiff;

};


#endif
