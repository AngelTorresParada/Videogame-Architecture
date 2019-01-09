#pragma once

#include "GameObject.h"
#include "TransformComponent.h"

#define ENEMY_WIDTH 30.0f

class Enemy : public GameObject {

public:
	Enemy(Game *, float, float);
	virtual ~Enemy();
	virtual void Run();
	virtual Sprite *getSprite();
	virtual TransformComponent *getTransform();
	virtual void RecieveMessage(Message *);

	void setSpeed(float);

private:
	virtual void ProcessMessage(Message *);
	Sprite *sprite;
	TransformComponent *transform;

};