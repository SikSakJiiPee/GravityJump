#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
	GameObject();
	~GameObject();

	void checkCollision();

private:
	float posX;
	float posY;
};

#endif