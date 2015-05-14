#ifndef CREDITS_H
#define CREDITS_H

#include "Main.h"

class Credits
{
public:
	Credits();

	void Update(sf::RenderWindow &window);
	void Render(sf::RenderWindow &window);


	~Credits();
private:

	sf::Texture creditsTex;
	sf::Sprite creditsImg;

	sf::RectangleShape creditShape;
	sf::Vector2f creditSize;

	float scrollSpeed;
	float creditY;

};

#endif
