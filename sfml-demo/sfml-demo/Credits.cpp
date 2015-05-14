#include "Credits.h"


Credits::Credits()
{
	scrollSpeed = 5;

	creditsTex.loadFromFile("Texture/credits.png");
	creditsTex.setRepeated(false);
	creditsTex.setSmooth(false);
	creditsImg.setTexture(creditsTex);
	creditsImg.setPosition(-120,100);
	creditY = 0;
	creditsImg.setTextureRect(sf::IntRect(0, creditY, 1280, 720));
}


Credits::~Credits()
{
}

void Credits::Update(sf::RenderWindow &window)
{
	if (creditY <= 5100)
	{
		creditY += scrollSpeed;
	}
	else if (creditY >= 5100)
	{
		creditY += 0.2;
	}
	else if (creditY >= 6500)
	{
		creditY = 0;
	}
	creditsImg.setTextureRect(sf::IntRect(0, creditY, 1280, 720));
}

void Credits::Render(sf::RenderWindow &window)
{
	window.draw(creditsImg);
}