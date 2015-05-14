#include "Background.h"


Background::Background()
{
	bgSpeed = 25;

	backgroundTex.loadFromFile("Texture/matriisi.jpg");
	backgroundTex.setRepeated(true);
	backgroundTex.setSmooth(false);

	backgroundImg.setPosition(0, 0);

	backgroundImg.setTexture(backgroundTex);
	bgY = 0;
	backgroundImg.setTextureRect(sf::IntRect(0, bgY, 5000, 3750));

}

Background::~Background()
{
}

void Background::Update(sf::RenderWindow &window)
{
	if (bgY < 100)
	{
		bgY += bgSpeed;
	}
	else
	{
		bgY = 0;
	}
	backgroundImg.setTextureRect(sf::IntRect(0, bgY, 5000, 3750));
}

void Background::Render(sf::RenderWindow &window)
{
	window.draw(backgroundImg);
}