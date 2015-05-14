#include "Player.h"


int main()
{
	sf::Vector2i screenDimensions(1280, 720);

	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y, 32), "GravityJump 0.05");
	window.setFramerateLimit(60);

	Tile tile;
	tile.loadColMap();
	tile.loadTileMap();


	sf::Texture playerTex;
	playerTex.loadFromFile("Texture/testi.png");

	sf::Texture player2Tex;
	player2Tex.loadFromFile("Texture/testi2.png");

	Background background;
	Credits credits;

	Player p1(Player(sf::Vector2f(70, 80), playerTex, 1));
	Player p2(Player(sf::Vector2f(70, 120), player2Tex, 2));

	// Creating views for split screen
	sf::View view1, view2, view3;

	view1.setViewport(sf::FloatRect(0, 0, 0.5f, 1.0f));
	view1.setSize(screenDimensions.x / 2, screenDimensions.y);

	view2.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1.0f));
	view2.setSize(screenDimensions.x / 2, screenDimensions.y);

	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
	sf::Vector2f position2(position);
	// -------------------


	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}

		}



		background.Update(window);
		
		switch (p1.gameEnd || p2.gameEnd)
		{
		case true:

			view3.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
			view3.setSize(screenDimensions.x, screenDimensions.y);
			window.setView(view3);

			window.clear();
			credits.Update(window);
			credits.Render(window);
			window.display();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				p1.gameEnd = false;
				p2.gameEnd = false;
			}

			break;

		default:
			p1.playerPos = p1.playerSprite.getPosition();
			p2.playerPos = p2.playerSprite.getPosition();
			//Window scrolling / Split screen ------------------------
			window.setView(view1);
			background.Render(window);

			for (int c = 0; c < tile.map.size(); c++)
			{
				for (int g = 0; g < tile.map[c].size(); g++)
				{
					if (tile.map[c][g].x != -1 && tile.map[c][g].y != -1)
					{
						tile.tiles.setPosition(g * 32, c * 32);
						tile.tiles.setTextureRect(sf::IntRect(tile.map[c][g].x * 32, tile.map[c][g].y * 32, 32, 32));
						window.draw(tile.tiles);
					}
				}
			}

			//Scrolling
			if (p1.playerSprite.getPosition().x + 10 >= view1.getSize().x / 2)
			{
				position.x = p1.playerSprite.getPosition().x + 10;
			}
			else
			{
				position.x = view1.getSize().x / 2;
			}

			if (p1.playerSprite.getPosition().y + 10 >= view1.getSize().y / 2)
			{
				position.y = p1.playerSprite.getPosition().y + 10;
			}
			else
			{
				position.y = view1.getSize().y / 2;
			}
			//------Scrolling

			if (p1.playerSprite.getPosition().y + 10 >= view1.getSize().y / 2)
				position.y = p1.playerSprite.getPosition().y + 10;
			else
				position.y = view1.getSize().y / 2;

			view1.setCenter(position);



			window.draw(p1.playerSprite);
			window.draw(p2.playerSprite);

			window.setView(view2);
			background.Render(window);

			for (int c = 0; c < tile.map.size(); c++)
			{
				for (int g = 0; g < tile.map[c].size(); g++)
				{
					if (tile.map[c][g].x != -1 && tile.map[c][g].y != -1)
					{
						tile.tiles.setPosition(g * 32, c * 32);
						tile.tiles.setTextureRect(sf::IntRect(tile.map[c][g].x * 32, tile.map[c][g].y * 32, 32, 32));
						window.draw(tile.tiles);
					}
				}
			}
			//Scrolling
			if (p2.playerSprite.getPosition().x + 10 >= view2.getSize().x / 2)
			{
				position2.x = p2.playerSprite.getPosition().x + 10;
			}
			else
			{
				position2.x = view2.getSize().x / 2;
			}

			if (p2.playerSprite.getPosition().y + 10 >= view2.getSize().y / 2)
			{
				position2.y = p2.playerSprite.getPosition().y + 10;
			}
			else
			{
				position2.y = view2.getSize().y / 2;
			}
			//------Scrolling

			if (p2.playerSprite.getPosition().y + 10 >= view2.getSize().y / 2)
				position2.y = p2.playerSprite.getPosition().y + 10;
			else
				position2.y = view2.getSize().y / 2;

			view2.setCenter(position2);
			window.draw(p2.playerSprite);
			window.draw(p1.playerSprite);



			//Window scrolling / Split screen ------------------------
			window.display();
			window.clear();

			p1.Update(playerTex, tile);
			p2.Update(playerTex, tile);
			p1.getPlayerdistance(p1, p2);
			p1.setBackFunct(p1, p2);
			p2.setBackFunct(p2, p1);

			break;
		}

		/*if (p1.gameEnd == true || p2.gameEnd == true)
		{
			
		}
		else if (p1.gameEnd == false || p2.gameEnd == false)
		{*/

		


#pragma region Liikkuminen
			//LIIKKUMINEN

			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && collidingRight == false) // Oikealle liikkuminen
			//{
			//	
			//		p1.playerSprite.move(4, 0);
			//		movingRight = true;

			//	if (collidingWall == false)
			//	{
			//			collidingRight = false;
			//			collidingUp = false;
			//			collidingDown = false;
			//			collidingLeft = false;
			//	}

			//	collidingLeft = false;
			//}
			//else
			//movingRight = false;

			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&& collidingLeft == false) // Vasemmalle liikkuminen
			//{
			//			p1.playerSprite.move(-4, 0);
			//			movingLeft = true;

			//			if (collidingWall == false)
			//			{
			//				collidingRight = false;
			//				collidingUp = false;
			//				collidingDown = false;
			//				collidingLeft = false;
			//			}

			//			collidingRight = false;
			//}
			//else
			//movingLeft = false;

			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& collidingUp == false) // Ylöspäin liikkuminen
			//{
			//	p1.playerSprite.move(0, -4);
			//	movingUp = true;
			//	if (collidingWall == false)
			//	{
			//		collidingRight = false;
			//		collidingUp = false;
			//		collidingDown = false;
			//		collidingLeft = false;
			//	}

			//	collidingDown = false;
			//}
			//else
			//movingUp = false;
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& collidingDown == false) // Alaspäin liikkuminen
			//{
			//	p1.playerSprite.move(0,4);
			//	movingDown = true;

			//	if (collidingWall == false)
			//	{
			//		collidingRight = false;
			//		collidingUp = false;
			//		collidingDown = false;
			//		collidingLeft = false;
			//	}
			//	collidingUp = false;
			//}	
			//else
			//movingDown = false;
			//LIIKKUMINEN LOPPU

			//if (movingRight == true && collidingWall == true && collidingLeft == false)
			//{
			//	p1.playerSprite.move(-4, 0);
			//	p1.playerSprite.setPosition(p1.playerSprite.getPosition().x - 5, p1.playerSprite.getPosition().y);
			//	collidingRight = true;
			//	collidingLeft = false;
			//	//collidingWall = false;
			//}
			//

			//if (movingLeft == true && collidingWall == true && collidingRight == false)
			//{
			//	p1.playerSprite.move(4, 0);
			//	p1.playerSprite.setPosition(p1.playerSprite.getPosition().x + 5, p1.playerSprite.getPosition().y);
			//	collidingLeft = true;
			//	collidingRight = false;
			//	//collidingWall = false;
			//}


			//if (movingUp == true && collidingWall == true && collidingDown == false)
			//{
			//	p1.playerSprite.move(0, 4);
			//	p1.playerSprite.setPosition(p1.playerSprite.getPosition().x, p1.playerSprite.getPosition().y + 5);
			//	collidingUp = true;
			//	collidingDown = false;
			//}


			//if (movingDown == true && collidingWall == true && collidingUp == false)
			//{
			//	p1.playerSprite.move(0, -4);
			//	p1.playerSprite.setPosition(p1.playerSprite.getPosition().x, p1.playerSprite.getPosition().y - 5);
			//	collidingDown = true;
			//	collidingUp = false;
			//}
			//
			//if (collidingDown == true)
			//{
			//	collidingUp = false;
			//}

			//if (collidingLeft == true)
			//{
			//	collidingRight = false;
			//}



#pragma endregion Liikkuminen



			//Collision check
			//for (int i = 0; i < p1.tilesP.size(); i++)
			//{
			//	if (colMap[p1.tilesP[i].y][p1.tilesP[i].x] == 1)
			//	{
			//		p1.collidingWall = true;
			//		//std::cout << "ITS A WALL ";
			//		break;
			//	}
			//	else if (colMap[p1.tilesP[i].y][p1.tilesP[i].x] == 2)
			//	{
			//		std::cout << "ITS A TARP!";
			//		break;
			//	}
			//	else
			//	{
			//		p1.collidingWall = false;
			//	}
			//}


		
	}

}

