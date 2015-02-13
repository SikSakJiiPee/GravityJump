#include "Player.h"


Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	rect.setPosition(position);
	rect.setSize(size);
	rect.setFillColor(color);
}


Player::~Player()
{
}

void Player::Update()
{
	bottom = rect.getPosition().y + rect.getSize().y;
	left = rect.getPosition().x;
	right = rect.getPosition().x + rect.getSize().x;
	top = rect.getPosition().y;
}

bool Player::collisionLeft(Player p)
{
	if (right < p.left || left > p.right || top > p.bottom || bottom < p.top)
	{
		return false;
	}
	else if (left < p.right && right > p.left + 20)
	{
		return true;
	}
}
bool Player::collisionRight(Player p)
{
	if (right < p.left || left > p.right || top > p.bottom || bottom < p.top)
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
