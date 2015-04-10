#include "Main.h"
#include "Player.h"
#include "Tile.h"


int main()
{
	sf::Vector2i screenDimensions(640, 480);

	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y, 32), "GravityJump 0.03a");
	window.setFramerateLimit(60);

	Tile tile;
	tile.loadColMap();
	tile.loadTileMap();


	sf::Texture playerTex;
	playerTex.loadFromFile("Texture/testi.png");

	sf::Texture backgroundTex;
	sf::Sprite backgroundImg;
	backgroundTex.loadFromFile("Texture/backround1.jpg");

	backgroundImg.setTexture(backgroundTex);
	backgroundImg.setScale(1.0f, (float)screenDimensions.y / backgroundTex.getSize().y);

	Player p1(Player(sf::Vector2f(70, 40), playerTex));

	// Creating views for split screen
	sf::View view1, view2;

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
				//Window scrolling / Split screen ------------------------
				window.setView(view1);
				window.draw(backgroundImg);

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

				view1.setCenter(position);
				view2.setCenter(position2);

				
				window.draw(p1.playerSprite);
				
				window.setView(view2);
				window.draw(backgroundImg);
				window.draw(p1.playerSprite);

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
				
				//Window scrolling / Split screen ------------------------
				window.display();
				window.clear();

				p1.Update(playerTex, tile);


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

