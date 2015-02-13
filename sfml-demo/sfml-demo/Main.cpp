#include "Main.h"



int main()
{
	sf::RenderWindow window(sf::VideoMode(1366, 768), "SFML demo");
	window.setFramerateLimit(60);
	sf::Event event;

	sf::Texture platformTex;
	platformTex.loadFromFile("Texture/platform_tex.png");
	sf::Sprite platformSpr;
	platformSpr.setTexture(platformTex);
	platformSpr.setPosition(100, 100);

	sf::Texture playerTex;
	playerTex.loadFromFile("Texture/player1.png");
	sf::Sprite playerSpr;
	playerSpr.setTexture(playerTex);
	playerSpr.setPosition(50, 10);



	while (window.isOpen())
	{
		while (window.pollEvent(event));
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//puhdistetaan ruutu mustalla
		window.clear(sf::Color::Black);

		//piirrä kaikki tähän..

		//window.draw(...);
		window.draw(platformSpr);
		window.draw(playerSpr);


		//----------------------------
		//LIIKKUMINEN

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			playerSpr.move(4.5, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			playerSpr.move(-4.5, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			playerSpr.move(0, -4.5);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			playerSpr.move(0, 4.5);
		}


		//LIIKKUMINEN LOPPU
		//----------------------------

		//end the current frame
		window.display();
	}



	return 0;
}