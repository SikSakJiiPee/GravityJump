//#include "Main.h"
//#include "Player.h"
//
//
//int main()
//{
//	bool collidingTop = false;
//	bool collidingBottom = false;
//	bool collidingRight = false;
//	//bool collidingLeft = false;
//
//	sf::RenderWindow window(sf::VideoMode(1366, 768), "SFML demo");
//	window.setFramerateLimit(60);
//	sf::Event event;
//
//	sf::Texture platformTex;
//	platformTex.loadFromFile("Texture/platform_tex.png");
//	sf::Sprite platformSpr;
//	platformSpr.setTexture(platformTex);
//	platformSpr.setPosition(100, 100);
//
//	sf::Texture playerTex;
//	playerTex.loadFromFile("Texture/player1.png");
//	sf::Sprite playerSpr;
//	playerSpr.setTexture(playerTex);
//	playerSpr.setPosition(50, 10);
//	
//	
//
//	//TESTAUSTA --- Commit test
//	Player p1(Player(sf::Vector2f(10, 10), sf::Vector2f(20, 20), sf::Color::Red));
//	Player p2(Player(sf::Vector2f(100, 100), sf::Vector2f(200, 200), sf::Color::Blue));
//	Player p3(Player(sf::Vector2f(5, 5), playerTex));
//
//	sf::FloatRect boundingBox = p3.playerSprite.getGlobalBounds();
//
//	while (window.isOpen())
//	{
//		while (window.pollEvent(event));
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//		//puhdistetaan ruutu mustalla
//		window.clear(sf::Color::Black);
//
//		p1.Update();
//		p2.Update();
//		p3.Update2();
//
//		if (p1.collisionTop(p2) == true)
//		{
//			std::cout << "TOP COLLIDED" << std::endl;
//			collidingTop = true;
//			p3.playerSprite.setRotation(180);
//			p1.rect.setRotation(180);
//		}
//		else
//			collidingTop = false;
//
//		if (p1.collisionBottom(p2) == true)
//		{
//			std::cout << "BOTTOM COLLIDED" << std::endl;
//			collidingBottom = true;
//		}
//		else
//			collidingBottom = false;
//
//	/*	if (p1.collisionLeft(p2) == true)
//		{
//			std::cout << "LEFT COLLIDED" << std::endl;
//			collidingLeft = true;
//		}
//		else
//			collidingLeft = false;*/
//
//	if (p1.collisionRight(p2) == true)
//		{
//			std::cout << "RIGHT COLLIDED" << std::endl;
//			collidingRight = true;
//		}
//		else
//			collidingRight = false;
//		
//		//piirrä kaikki tähän..
//
//		//window.draw(...);
//		window.draw(platformSpr);
//		window.draw(playerSpr);
//
//		window.draw(p1.rect);
//		window.draw(p2.rect);
//		window.draw(p3.playerSprite);
//
//
//		//----------------------------
//		//LIIKKUMINEN
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& collidingRight == false)
//		{
//			//playerSpr.move(4.5, 0);
//			p1.rect.move(4.5, 0);
//			p3.playerSprite.move(4.5, 0);
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//		{
//			//playerSpr.move(-4.5, 0);
//			p1.rect.move(-4.5,0);
//			p3.playerSprite.move(-4.5, 0);
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& collidingTop == false)
//		{
//			//playerSpr.move(0, -4.5);
//			p1.rect.move(0, -4.5);
//			p3.playerSprite.move(0,-4.5);
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& collidingBottom == false)
//		{
//			//playerSpr.move(0, 4.5);
//			p1.rect.move(0, 4.5);
//			p3.playerSprite.move(0,4.5);
//		}
//
//
//		//LIIKKUMINEN LOPPU
//		//----------------------------
//
//		//end the current frame
//		window.display();
//	}
//
//
//
//	return 0;
//}