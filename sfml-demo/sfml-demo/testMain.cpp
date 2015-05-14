#include "Player.h"
#include "Menu.h"



int main()
{
	sf::Vector2i screenDimensions(1280, 720);


	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y, 32), "GravityJump 0.05");
	window.setFramerateLimit(60);
	

	//Music
	sf::SoundBuffer menuBuf;
	if (!menuBuf.loadFromFile("music/gj_menu.wav"))
		return -1;
	sf::Sound menuBGM;
	menuBGM.setBuffer(menuBuf);

	sf::SoundBuffer gameBuf;
	if (!gameBuf.loadFromFile("music/gj_game.wav"))
		return -1;
	sf::Sound gameBGM;
	gameBGM.setBuffer(gameBuf);

	sf::SoundBuffer winBuf;
	if (!winBuf.loadFromFile("music/gj_win.wav"))
		return -1;
	sf::Sound winBGM;
	winBGM.setBuffer(winBuf);

	//SFX
	sf::SoundBuffer buttonMoveBuf;
	if (!buttonMoveBuf.loadFromFile("SFX/button_move.wav"))
		return -1;
	sf::Sound buttonMoveSFX;
	buttonMoveSFX.setBuffer(buttonMoveBuf);

	sf::SoundBuffer buttonSelectBuf;
	if (!buttonSelectBuf.loadFromFile("SFX/button_select.wav"))
		return -1;
	sf::Sound buttonSelectSFX;
	buttonSelectSFX.setBuffer(buttonSelectBuf);

	

	bool looping = false;
	
	//----

	menuBGM.setLoop(true);
	menuBGM.play();


	Menu menu(&window);

	/////
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.Moveup();
					buttonMoveSFX.play();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					buttonMoveSFX.play();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
					{
						std::cout << "Play button painettu" << std::endl;
						buttonSelectSFX.play();

						menuBGM.stop();
						gameBGM.setLoop(true);
						gameBGM.play();

						Tile tile;
						tile.loadColMap();
						tile.loadTileMap();


						sf::Texture playerTex;
						playerTex.loadFromFile("Texture/testi.png");

						sf::Texture player2Tex;
						player2Tex.loadFromFile("Texture/testi2.png");

						Background background;
						Credits credits;

						Player p1(Player(sf::Vector2f(224, 2430), playerTex, 1));
						Player p2(Player(sf::Vector2f(280, 2430), player2Tex, 2));

						p1.currentCheckpoint.x = 224;
						p1.currentCheckpoint.y = 2430;

						p1.playerOrigin.x = 224;
						p1.playerOrigin.y = 2430;

						p2.currentCheckpoint.x = 280;
						p2.currentCheckpoint.y = 2430;

						p2.playerOrigin.x = 280;
						p2.playerOrigin.y = 2430;

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
							p1.Update(playerTex, tile);
							p2.Update(playerTex, tile);
							
	
						

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

							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
							{
								window.close();
							}

							background.Update(window);

							switch (p1.gameEnd || p2.gameEnd)
							{
							case true:


								if (looping == false)
								{
									gameBGM.stop();
									winBGM.play();
									winBGM.setLoop(true);
									looping = true;
								}

								view3.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
								view3.setSize(screenDimensions.x, screenDimensions.y);
								window.setView(view3);

								window.clear();
								credits.Update(window);
								credits.Render(window);
								window.display();

								if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
								{
									p1.playerSprite.setPosition(p1.playerOrigin.x, p1.playerOrigin.y);
									p2.playerSprite.setPosition(p2.playerOrigin.x, p2.playerOrigin.y);

									p1.gameEnd = false;
									p2.gameEnd = false;

									winBGM.stop();
									gameBGM.play();
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

								
								p1.getPlayerdistance(p1, p2);
								p1.setBackFunct(p1, p2);
								p2.setBackFunct(p1, p2);

								break;
							}
						}

						break;
					}
					case 1:
						std::cout << "Options button painettu" << std::endl;
						buttonSelectSFX.play();
						break;
					case 2:
						buttonSelectSFX.play();
						window.close();
						std::cout << "window closed" << std::endl;
						break;
					}
					break;
				}
			}

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

		}

		window.clear();

		menu.draw(&window);

		window.display();
		
	}
	return 0;
}

	//////






