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

bool Player::Collision(Player p)
{
	if (right < p.left || left > p.right || top > p.bottom || bottom < p.top)
	{
		return false;
	}
	return true;
}