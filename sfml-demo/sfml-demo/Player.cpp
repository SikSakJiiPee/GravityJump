#include "Player.h"
#include "Main.h"

std::vector<std::vector<bool>> mask;



Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	rect.setPosition(position);
	rect.setSize(size);
	rect.setFillColor(color);
}
Player::Player(sf::Vector2f position, sf::Texture &playerTexture)
{

	playerImg = playerTexture.copyToImage();
	
	for (int i = 0; i < playerImg.getSize().x; i++)
	{
		std::vector<bool> tempMask;
		for (int j = 0; j < playerImg.getSize().y; j++)
		{
			if (playerImg.getPixel(i, j).a > 0)
				tempMask.push_back(true);
			else
				tempMask.push_back(false);
		}
		mask.push_back(tempMask);
	}
	playerSprite.setPosition(position);
	playerSprite.setTexture(playerTexture);

	

}

Player::~Player()
{
}

void Player::Update(sf::Texture &playerTexture)
{
	playerImg = playerTexture.copyToImage();

	bottom = playerSprite.getPosition().y + playerImg.getSize().y;
	left = playerSprite.getPosition().x;
	right = playerSprite.getPosition().x + playerImg.getSize().x;
	top = playerSprite.getPosition().y;
}
void Player::Update2()
{

	//bottom = playerSprite.getPosition().y + player.getSize().y;
	left = playerSprite.getPosition().x;
	//right = playerSprite.getPosition().x + playerSprite.getSize().x;
	top = rect.getPosition().y;
}

bool Player::collisionLeft(Player p)
{
	if (right < p.left || left > p.right || top > p.bottom || bottom < p.top)
	{
		return false;
	}
	else // if (left < p.right && right > p.left + 20)
	{
		return true;
	}
}
bool Player::collisionRight(Player p)
{
	if (right < p.left  || left > p.right || top > p.bottom || bottom < p.top)
	{
		return false;
	}
	else if (right > p.left && left < p.right - 20)
	{
		return true;
	}
}
bool Player::collisionTop(Player p)
{
	if (right < p.left || left > p.right || top > p.bottom || bottom < p.top)
	{
		return false;
	}
	else if (top < p.bottom && bottom > p.top + 20)
	{
		return true;
	}
}
bool Player::collisionBottom(Player p)
{
	if (right < p.left || left > p.right || top > p.bottom || bottom < p.top)
	{
		return false;
	}
	else if (bottom > p.top && top < p.bottom - 20)
	{
		return true;
	}
}
