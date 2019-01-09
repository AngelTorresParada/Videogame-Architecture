#pragma once
#include "GameObject.h"

#define BULLET_SPEED 10.0f

class Bullet : public GameObject {

public:
	enum Owner {
		PLAYER,
		ENEMY,
	};

	Bullet(Game *, float, float, Owner);
	virtual ~Bullet();
	virtual void Run();
	virtual Sprite *getSprite();
	virtual TransformComponent *getTransform();
	virtual void RecieveMessage(Message *);

	Owner getOwner();

private:
	virtual void ProcessMessage(Message *);
	void SendMessage(Message *);
	Sprite *sprite;
	TransformComponent *transform;
	Owner owner;

};