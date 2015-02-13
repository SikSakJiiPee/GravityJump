#include "Main.h"
#include "Player.h"


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

	//TESTAUSTA --- Commit test
	Player p1(Player(sf::Vector2f(10, 10), sf::Vector2f(20, 20), sf::Color::Red)),
		p2(Player(sf::Vector2f(100, 100), sf::Vector2f(20, 20), sf::Color::Blue));

	while (window.isOpen())
	{
		while (window.pollEvent(event));
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//puhdistetaan ruutu mustalla
		window.clear(sf::Color::Black);


		p1.Update();
		p2.Update();
		if (p1.Collision(p2))
		{
			std::cout << "P1 collided with P2" << std::endl;
		}
		//piirrä kaikki tähän..

		//window.draw(...);
		window.draw(platformSpr);
		window.draw(playerSpr);

		window.draw(p1.rect);
		window.draw(p2.rect);


		//----------------------------
		//LIIKKUMINEN

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			playerSpr.move(4.5, 0);
			p1.rect.move(4.5, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			playerSpr.move(-4.5, 0);
			p1.rect.move(-4.5,0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			playerSpr.move(0, -4.5);
			p1.rect.move(0, -4.5);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			playerSpr.move(0, 4.5);
			p1.rect.move(0, 4.5);
		}


		//LIIKKUMINEN LOPPU
		//----------------------------

		//end the current frame
		window.display();
	}



	return 0;
}